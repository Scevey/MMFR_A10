// Paul Lampanaro
#ifndef __MYBOUNDINGOBJECTMANAGER_H_
#define __MYBOUNDINGOBJECTMANAGER_H_

#include "RE\ReEng.h"
#include "MyBoundingCubeClass.h"

class MyBoundingObjectManager
{
private:
	std::vector<MyBoundingCubeClass*> m_lObjects; // using Cube, which has to have Sphere collision as well

public:
	// get and release instance methods
	static MyBoundingObjectManager& GetInstance();

	// required methods
	void AddBoundingObject(std::vector<vector3> a_lVectorList);
	void SetVisibility(int a_index, bool a_visible); 
	void SetColor(int a_index, vector3 a_color);
	int GetCount(void);
	void RenderBoundingObject(MeshManagerSingleton* a_meshMngr, int a_index);
	void RenderAll(void);
	void UpdateBoundingObject(std::vector<vector3> a_lVectorList, int a_index); // not sure how the motion will be handled in this method
	void CheckCollisions();

	void ToggleVisibility(void);

};

#endif //__MYBOUNDINGOBJECTMANAGER_H__
