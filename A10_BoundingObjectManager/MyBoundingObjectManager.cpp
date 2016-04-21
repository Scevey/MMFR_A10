// Paul Lampanaro
#include "MyBoundingObjectManager.h"

MyBoundingObjectManager& MyBoundingObjectManager::GetInstance()
{
	static MyBoundingObjectManager instance;
	return instance;
}

void MyBoundingObjectManager::AddBoundingObject(std::vector<vector3> a_lVectorList)
{
	// create a new bounding object and add it to the list
	MyBoundingCubeClass* newBoundingObject = new MyBoundingCubeClass(a_lVectorList);
	m_lObjects.push_back(newBoundingObject);
}

void MyBoundingObjectManager::SetVisibility(int a_index, bool a_visible)
{
	m_lObjects[a_index]->SetVisibility(a_visible);
}

void MyBoundingObjectManager::ToggleVisibility()
{
	//loop through the list of objects
	for (int i = 0; i < m_lObjects.size(); i++) {
		//if the visibilty is on
		if (m_lObjects[i]->GetVisibility()) {
			//turn it off
			SetVisibility(i, false);
		}
		else
		{
			//else turn it on
			SetVisibility(i, true);
		}
	}
}

void MyBoundingObjectManager::SetColor(int a_index, vector3 a_color)
{
	m_lObjects[a_index]->SetColor(a_color);
}

int MyBoundingObjectManager::GetCount(void)
{
	return m_lObjects.size();
}

//cubes
void MyBoundingObjectManager::RenderBoundingObject(MeshManagerSingleton* a_meshMngr, String id, vector3 radius, int a_index)
{
	// syntax for adding a single bounding box to mesh manager
	vector3 centerTemp = m_lObjects[a_index]->GetCenterG();
	matrix4 m_m4Temp = a_meshMngr->GetModelMatrix(id) * glm::translate(centerTemp);

	if (m_lObjects[a_index]->GetVisibility()) {
		a_meshMngr->AddCubeToQueue(m_m4Temp * glm::scale(radius*2.0f), m_lObjects[a_index]->GetColor(), WIRE);
	}


}

//spheres
void MyBoundingObjectManager::RenderBoundingObject(MeshManagerSingleton* a_meshMngr, String id, float radius, int a_index)
{
	// syntax for adding a single bounding box to mesh manager
	vector3 centerTemp = m_lObjects[a_index]->GetCenterG();
	matrix4 m_m4Temp = a_meshMngr->GetModelMatrix(id) * glm::translate(centerTemp);

	if (m_lObjects[a_index]->GetVisibility()) {
		vector3 centerTemp = m_lObjects[a_index]->GetCenterG();
		matrix4 m_m4Temp = a_meshMngr->GetModelMatrix(id) * glm::translate(centerTemp);
		a_meshMngr->AddSphereToQueue(m_m4Temp * glm::scale(vector3(radius * 2.0f)), m_lObjects[a_index]->GetColor(), WIRE);
	}


}

void MyBoundingObjectManager::RenderAll(void)
{
	// syntax for adding all bounding box
}

void MyBoundingObjectManager::UpdateBoundingObject(std::vector<vector3> a_lVectorList, int a_index)
{
	m_lObjects[a_index]->CalculateBoundingDimensions(a_lVectorList); 
}

void MyBoundingObjectManager::CheckCollisions(void)
{
	// reset color of all objects to green
	for (int i = 0; i < m_lObjects.size(); i++)
	{
		m_lObjects[i]->SetColor(REGREEN);
	}

	// loop through each and check for collisions
	for (int i = 0; i < m_lObjects.size(); i++)
	{
		for (int j = 0; j < m_lObjects.size(); j++)
		{
			if (i == j) continue; // do not check collision with itself

			// if they are colliding, set them to red
			if (m_lObjects[i]->IsColliding(m_lObjects[j]))
			{
				m_lObjects[i]->SetColor(RERED);
				m_lObjects[j]->SetColor(RERED);
			}
		}
	}
}