#include "stdafx.h"
#include "cMainGame.h"


cMainGame::cMainGame()
	: m_hBitmap(NULL), 
	 m_vEye(0,0,-5), 
	 m_vLookAt(0,0,0), 
	 m_vUp(0,1,0), 
	 m_vPosition(0,0,0),
	 m_fBoxRotY(0.0f)
{
}


cMainGame::~cMainGame()
{
}

// >> : 

void cMainGame::Setup()
{
	HDC hdc = GetDC(g_hWnd);

	m_MemDC = CreateCompatibleDC(hdc);
	{
		RECT rc;
		GetClientRect(g_hWnd, &rc);
		m_hBitmap = CreateCompatibleBitmap(hdc, rc.right, rc.bottom);
		m_hOldBitmap = (HBITMAP)SelectObject(m_MemDC, m_hBitmap);
		ReleaseDC(g_hWnd, hdc);
	}

	{	// : vertex = 꼭지점
		m_vecVertex.push_back(cVector3(-1.0f, -1.0f, -1.0f));
		m_vecVertex.push_back(cVector3(-1.0f,  1.0f, -1.0f));
		m_vecVertex.push_back(cVector3( 1.0f,  1.0f, -1.0f));
		m_vecVertex.push_back(cVector3( 1.0f, -1.0f, -1.0f));
		m_vecVertex.push_back(cVector3(-1.0f, -1.0f,  1.0f));
		m_vecVertex.push_back(cVector3(-1.0f,  1.0f,  1.0f));
		m_vecVertex.push_back(cVector3( 1.0f,  1.0f,  1.0f));
		m_vecVertex.push_back(cVector3( 1.0f, -1.0f,  1.0f));
	}

	{	// index = 선			-> 방향성을 통일시켜서 삼각형을 그려줘야한다!(시계방향 or 반시계방향)
		m_vecIndex.push_back(0);
		m_vecIndex.push_back(1);
		m_vecIndex.push_back(2);

		m_vecIndex.push_back(0);
		m_vecIndex.push_back(2);
		m_vecIndex.push_back(3);

		m_vecIndex.push_back(4);
		m_vecIndex.push_back(6);
		m_vecIndex.push_back(5);

		m_vecIndex.push_back(4);
		m_vecIndex.push_back(7);
		m_vecIndex.push_back(6);

		m_vecIndex.push_back(4);
		m_vecIndex.push_back(5);
		m_vecIndex.push_back(1);

		m_vecIndex.push_back(4);
		m_vecIndex.push_back(1);
		m_vecIndex.push_back(0);

		m_vecIndex.push_back(3);
		m_vecIndex.push_back(2);
		m_vecIndex.push_back(6);

		m_vecIndex.push_back(3);
		m_vecIndex.push_back(6);
		m_vecIndex.push_back(7);

		m_vecIndex.push_back(1);
		m_vecIndex.push_back(5);
		m_vecIndex.push_back(6);

		m_vecIndex.push_back(1);
		m_vecIndex.push_back(6);
		m_vecIndex.push_back(2);

		m_vecIndex.push_back(4);
		m_vecIndex.push_back(0);
		m_vecIndex.push_back(3);

		m_vecIndex.push_back(4);
		m_vecIndex.push_back(3);
		m_vecIndex.push_back(7);
	}

	m_matWorld = cMatrix::Identity(4);
	m_matView = cMatrix::Identity(4);
	m_matProj = cMatrix::Identity(4);
	m_matViewport = cMatrix::Identity(4);
}


void cMainGame::Update()
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	m_vLookAt = m_vPosition;
	m_vEye = m_vEye + m_vPosition;
	cMatrix matR = cMatrix::RotationY(m_fBoxRotY);
	cMatrix matX = cMatrix::RotationX(m_fBoxRotX);
	cMatrix matZ = cMatrix::RotationZ(m_fBoxRotZ);
	m_matWorld = matR * matX * matZ * cMatrix::Translation(m_vPosition);
	m_matView = cMatrix::View(m_vEye, m_vLookAt, m_vUp);
	m_matProj = cMatrix::Projection(PI / 3.0f,	rc.right / (float)rc.bottom, 1.0f, 1000.0f);
	m_matViewport = cMatrix::Viewport(0, 0, rc.right, rc.bottom, 0, 1);
}

void cMainGame::Render(HDC hdc)
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	PatBlt(m_MemDC, rc.left, rc.top, rc.right, rc.bottom, WHITENESS);			
	// PatBlt = 패턴방식 초기화 : 지정한 사각영역을 현재 DC에 선택된 브러시로 채움
	// WHITENESS -> 칼라정의

	cMatrix matWVP = m_matWorld * m_matView * m_matProj;						// m_matWord = SRT 과정이 끝난 좌표를 말함

	for (size_t i = 0; i < m_vecIndex.size(); i += 3)							// index가 3단위로 뛰기 때문
	{
		cVector3 v1 = m_vecVertex[m_vecIndex[i + 0]];
		cVector3 v2 = m_vecVertex[m_vecIndex[i + 1]];
		cVector3 v3 = m_vecVertex[m_vecIndex[i + 2]];

		v1 = cVector3::TransformCoord(v1, matWVP);
		v2 = cVector3::TransformCoord(v2, matWVP);
		v3 = cVector3::TransformCoord(v3, matWVP);

		v1 = cVector3::TransformCoord(v1, m_matViewport);
		v2 = cVector3::TransformCoord(v2, m_matViewport);
		v3 = cVector3::TransformCoord(v3, m_matViewport);

		// : 여기서부턴 평면으로 갔기 때문에 z값이 필요없음
		MoveToEx(m_MemDC, v1.x, v1.y, NULL);									// MoveToEx : LineTo를 그리기 위한 시작점을 설정해주는 함수
		LineTo(m_MemDC, v2.x, v2.y);
		LineTo(m_MemDC, v3.x, v3.y);
		LineTo(m_MemDC, v1.x, v1.y);
	}

	BitBlt(hdc, 0, 0, rc.right, rc.bottom, m_MemDC, 0, 0, SRCCOPY);
	// BitBlt = 고속복사 : 메모리 DC의 비트맵을 현재 DC에 고속복사함
	// SRCCOPY : 소스 영역을 대상 영역에 복사함

}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
		break;
	case WM_LBUTTONUP:
		break;
	case WM_MOUSEMOVE:
		break;
	case WM_MOUSEWHEEL:
		break;
	case WM_KEYDOWN:
		if (wParam == VK_LEFT)
		{
			m_fBoxRotY += 0.02f;
		}
		else if (wParam == VK_RIGHT)
		{
			m_fBoxRotY -= 0.02f;
		}
		else if (wParam == VK_UP)
		{
			m_fBoxRotX += 0.02f;
		}
		else if (wParam == VK_DOWN)
		{
			m_fBoxRotX -= 0.02f;
		}
		break;
	}
}