#include "stdafx.h"
#include "cMainGame.h"

cMainGame::cMainGame()
{
}


cMainGame::~cMainGame()
{
}

// >> : 

void cMainGame::Setup()
{
}


void cMainGame::Update()
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	cMatrix matRX = cMatrix::RotationX(m_vCamRotAngle.x);
	cMatrix matRY = cMatrix::RotationY(m_vCamRotAngle.y);
	cMatrix matR = matRX * matRY;
	m_vEye = cVector3(0, 0, -m_fCameraDistance);
	m_vEye = cVector3::TransformCoord(m_vEye, matR);

	m_vLookAt = m_vPosition;
	m_vEye = m_vEye + m_vPosition;


	m_matWorld = matR * cMatrix::Translation(m_vPosition);
	m_matView = cMatrix::View(m_vEye, m_vLookAt, m_vUp);
	m_matProj = cMatrix::Projection(PI / 4.0f,
		rc.right / (float)rc.bottom, 1.0f, 1000.0f);
	m_matViewport = cMatrix::Viewport(0, 0, rc.right, rc.bottom, 0, 1);
}

void cMainGame::Render(HDC hdc)
{
	// : Box ±×¸®±â..

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
	}
}