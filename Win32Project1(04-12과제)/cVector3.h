#pragma once
class cVector3
{
public:
	cVector3();
	~cVector3();

	// >> : 
	float x, y, z; 

	// : 연산자 오버라이딩 해오기 
	bool operator==(cVector3& vec);
	bool operator!=(cVector3& vec);
	cVector3 operator+(cVector3& vec);
	cVector3 operator-(cVector3& vec);
	cVector3 operator*(float f);
	cVector3 operator/(float f);

	// : 내적 , 외적  
	static float Dot(cVector3& v1, cVector3& v2);
	static cVector3 Cross(cVector3& v1, cVector3& v2);
	float Length();
	cVector3 Normalize();
	// << :

	// >> : 
	cVector3(float _x, float _y, float _z); 

	static cVector3 TransformCoord(cVector3& v, cMatrix& mat); 
	static cVector3 TransformNormal(cVector3& v, cMatrix& mat); 
	
	// << ; 
};

