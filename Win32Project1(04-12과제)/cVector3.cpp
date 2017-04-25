#include "stdafx.h"
#include "cVector3.h"

#define EPSILON 0.0001f	/// : 사용 의미는 숙제 풀이할때 설명

cVector3::cVector3()
	// >> : 
	: x(0.0f) , y(0.0f), z(0.0f)
	// << : 
{
}


cVector3::~cVector3()
{
}

// >> : 이하 구현해 오기 
bool cVector3::operator==(cVector3& vec)
{	
	/*
		EPSILON  사용 의미 보이기. 메인함수 에서 
		float 형은 == 로 비교하지 말고 범위로 비교해야 한다는거 주의시킬것
	*/
	if (x - EPSILON <= vec.x && vec.x <= x + EPSILON &&
		y - EPSILON <= vec.y && vec.y <= y + EPSILON &&
		z - EPSILON <= vec.z && vec.z <= z + EPSILON)
	{
		return true;
	}
	return false;
}

bool cVector3::operator!=(cVector3& vec)
{
	return !(*this == vec);
}

// : 벡터 덧셈
cVector3 cVector3::operator+(cVector3& vec)
{
	cVector3 v;
	v.x = x + vec.x;
	v.y = y + vec.y;
	v.z = z + vec.z;
	return v;
}

// : 벡터 뺄셈
cVector3 cVector3::operator-(cVector3& vec)
{
	cVector3 v;
	v.x = x - vec.x;
	v.y = y - vec.y;
	v.z = z - vec.z;
	return v;
}

// : 벡터 스칼라 곱셈
cVector3 cVector3::operator*(float f)
{
	cVector3 v;
	v.x = x * f;
	v.y = y * f;
	v.z = z * f;
	return v;
}

// : 벡터 스칼라 나눗셈
cVector3 cVector3::operator/(float f)
{
	cVector3 v;
	v.x = x / f;
	v.y = y / f;
	v.z = z / f;
	return v;
}

// : 내적 -> 결과값 스칼라
float cVector3::Dot(cVector3& v1, cVector3& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

// >> : 외적 -> 두 벡터에 수직한 벡터
cVector3 cVector3::Cross(cVector3& v1, cVector3& v2)
{
	cVector3 v;
	v.x = v1.y * v2.z - v1.z * v2.y;
	v.y = v1.z * v2.x - v1.x * v2.z;
	v.z = v1.x * v2.y - v1.y * v2.x;
	return v;
}

// : 길이
float cVector3::Length()
{
	return (float)sqrt(x * x + y * y + z * z);	// : 사용 math.h
}

// : 단위 벡터 
cVector3 cVector3::Normalize()
{
	float l = Length();
	cVector3 v;
	v.x = x / l;
	v.y = y / l;
	v.z = z / l;
	return v;
}
// << :
cVector3::cVector3(float _x, float _y, float _z)
	: x(_x), y(_y), z(_z)
{
}

cVector3 cVector3::TransformCoord(cVector3 & v, cMatrix& mat)
{
	cVector3 vRet; 

	vRet.x = v.x * mat[0][0] + v.y *mat[1][0] + v.z *mat[2][0] + 1.0f * mat[3][0]; 
	vRet.y = v.x * mat[0][1] + v.y *mat[1][1] + v.z *mat[2][1] + 1.0f * mat[3][1];
	vRet.z = v.x * mat[0][2] + v.y *mat[1][2] + v.z *mat[2][2] + 1.0f * mat[3][2];
	float w = v.x * mat[0][3] + v.y *mat[1][3] + v.z *mat[2][3] + 1.0f * mat[3][3];
	
	if (-EPSILON > w || EPSILON < w)
	{
		vRet.x /= w; 
		vRet.y /= w; 
		vRet.z /= w; 
	}

	return vRet; 
}

cVector3 cVector3::TransformNormal(cVector3& v, cMatrix& mat)
{
	cVector3 vRet; 
	vRet.x = v.x * mat[0][0] + v.y * mat[1][0] + v.z * mat[2][0]; 
	vRet.y = v.x * mat[0][1] + v.y * mat[1][1] + v.z * mat[2][1];
	vRet.z = v.x * mat[0][2] + v.y * mat[1][2] + v.z * mat[2][2];

	return vRet; 
}
