// Paul Lampanaro
#include "MyBoundingObjectManager.h"

MyBoundingObjectManager* MyBoundingObjectManager::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new MyBoundingObjectManager();
	}
	return m_pInstance;
}

void MyBoundingObjectManager::ReleaseInstance()
{
	if (m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
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

void MyBoundingObjectManager::SetColor(int a_index, vector3 a_color)
{
	m_lObjects[a_index]->SetColor(a_color);
}

int MyBoundingObjectManager::GetCount(void)
{
	return m_lObjects.size();
}

void MyBoundingObjectManager::RenderBoundingObject(MeshManagerSingleton* a_meshMngr, int a_index)
{
	// syntax for adding a single bounding box to mesh manager
}

void MyBoundingObjectManager::RenderAll(void)
{
	// syntax for adding all bounding box
}

void MyBoundingObjectManager::UpdateBoundingObject(std::vector<vector3> a_lVectorList, int a_index)
{
	m_lObjects[a_index]->CalculateBoundingDimensions(); 
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
		for (int j = 0; j < m_lObjects.size(); i++)
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