#include "MyBoundingSphereClass.h"
//  MyBoundingSphereClass
void MyBoundingSphereClass::Init(void)
{
	m_fRadius = 0.0f;
	m_m4ToWorld = IDENTITY_M4;
	isVisible = false;
	m_v3Center = vector3(0.0f);
	m_v3Min = vector3(0.0f);
	m_v3Max = vector3(0.0f);
}
void MyBoundingSphereClass::Swap(MyBoundingSphereClass& other)
{
	std::swap(m_fRadius, other.m_fRadius);
	std::swap(m_m4ToWorld, other.m_m4ToWorld);

	std::swap(m_v3Center, other.m_v3Center);
	std::swap(m_v3Min, other.m_v3Min);
	std::swap(m_v3Max, other.m_v3Max);
}
void MyBoundingSphereClass::Release(void)
{

}
//The big 3
MyBoundingSphereClass::MyBoundingSphereClass(std::vector<vector3> a_lVectorList)
{
	uint nVertexCount = a_lVectorList.size();
	if (nVertexCount > 0)
	{
		m_v3Min = a_lVectorList[0];
		m_v3Max = a_lVectorList[0];
	}

	for (uint i = 0; i < nVertexCount; i++)
	{
		if (a_lVectorList[i].x > m_v3Max.x)
			m_v3Max.x = a_lVectorList[i].x;
		else if (a_lVectorList[i].x < m_v3Min.x)
			m_v3Min.x = a_lVectorList[i].x;

		if (a_lVectorList[i].y > m_v3Max.y)
			m_v3Max.y = a_lVectorList[i].y;
		else if (a_lVectorList[i].y < m_v3Min.y)
			m_v3Min.y = a_lVectorList[i].y;

		if (a_lVectorList[i].z > m_v3Max.z)
			m_v3Max.z = a_lVectorList[i].z;
		else if (a_lVectorList[i].z < m_v3Min.z)
			m_v3Min.z = a_lVectorList[i].z;
	}

	m_v3Center = (m_v3Max + m_v3Min) / 2.0f;
	m_fRadius = glm::distance(m_v3Center, m_v3Max);

	//m_pSphere = new PrimitiveClass();
	//m_pSphere->GenerateSphere(m_fRadius, 10, REGREEN);

}
MyBoundingSphereClass::MyBoundingSphereClass(MyBoundingSphereClass const& other)
{
	m_fRadius = other.m_fRadius;
	m_m4ToWorld = other.m_m4ToWorld;

	m_v3Center = other.m_v3Center;
	m_v3Min = other.m_v3Min;
	m_v3Max = other.m_v3Max;
}
MyBoundingSphereClass& MyBoundingSphereClass::operator=(MyBoundingSphereClass const& other)
{
	if(this != &other)
	{
		Release();
		Init();
		MyBoundingSphereClass temp(other);
		Swap(temp);
	}
	return *this;
}
MyBoundingSphereClass::~MyBoundingSphereClass(){Release();};
//Accessors
void MyBoundingSphereClass::SetModelMatrix(matrix4 a_m4ToWorld){ m_m4ToWorld = a_m4ToWorld; }
vector3 MyBoundingSphereClass::GetCenter(void){ return vector3(m_m4ToWorld * vector4(m_v3Center, 1.0f)); }
vector3 MyBoundingSphereClass::GetMax(void) { return vector3(m_m4ToWorld * vector4(m_v3Max, 1.0f)); }
vector3 MyBoundingSphereClass::GetMin(void) { return vector3(m_m4ToWorld * vector4(m_v3Min, 1.0f)); }
vector3 MyBoundingSphereClass::GetColor(void) { return color; }
matrix4 MyBoundingSphereClass::GetModelMatrix(void) { return m_m4ToWorld; }
float MyBoundingSphereClass::GetRadius(void) { return m_fRadius; }
bool MyBoundingSphereClass::GetVisibility() {
	return isVisible;
}
//--- Non Standard Singleton Methods
bool MyBoundingSphereClass::IsColliding(MyBoundingSphereClass* const a_pOther)
{
	vector3 m_v3Center1 = a_pOther->GetCenter();
	vector3 v3Temp = GetCenter();
	vector3 v3Temp1 = a_pOther->GetCenter();
	if (glm::distance(v3Temp, v3Temp1) < m_fRadius + a_pOther->GetRadius()) {
		SetColor(RERED);
		a_pOther->SetColor(RERED);
		return true;
	}
	else {
		SetColor(REWHITE);
		a_pOther->SetColor(REWHITE);
		return false;
	}
}
void MyBoundingSphereClass::ToggleVisible() {
	isVisible = !isVisible;
}
void MyBoundingSphereClass::UpdatePosition(vector3 a_v3Input) { 
	return;
}

void MyBoundingSphereClass::SetColor(vector3 a_Color) {
	color = a_Color;
}