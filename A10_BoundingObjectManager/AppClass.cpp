#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("MyBoundingSphereClass example"); // Window Name

	// Set the clear color based on Microsoft's CornflowerBlue (default in XNA)
	//if this line is in Init Application it will depend on the .cfg file, if it
	//is on the InitVariables it will always force it regardless of the .cfg
	m_v4ClearColor = vector4(0.4f, 0.6f, 0.9f, 0.0f);
}

void AppClass::InitVariables(void)
{
	//Initialize positions
	m_v3O1 = vector3(-2.5f, 0.0f, 0.0f);
	m_v3O2 = vector3(2.5f, 0.0f, 0.0f);

	//Load Models
	m_pMeshMngr->LoadModel("Minecraft\\Steve.obj", "Steve");
	m_pMeshMngr->LoadModel("Minecraft\\Creeper.obj", "Creeper");

	m_BOM = new MyBoundingObjectManager(); // banana

	std::vector<vector3> vertexList = m_pMeshMngr->GetVertexList("Steve");
	m_BCC1 = new MyBoundingCubeClass(vertexList);

	m_BOM->AddBoundingObject(vertexList); // banana

	//m_pCube1 = new PrimitiveClass();
	m_fRadius1x = m_BCC1->GetRadiusX();
	m_fRadius1y = m_BCC1->GetRadiusY();
	m_fRadius1z = m_BCC1->GetRadiusZ();
	m_v3Center1 = m_BCC1->GetCenterG();
	//m_pCube1->GenerateSphere(m_fRadius1, 10, REGREEN);
	//m_pCube1->GenerateCube(m_fRadius1 * 2, REGREEN);

	//Creeper
	vertexList = m_pMeshMngr->GetVertexList("Creeper");
	m_BCC2 = new MyBoundingSphereClass(vertexList);

	m_BOM->AddBoundingObject(vertexList); // banana

	m_fRadius2 = m_BCC2->GetRadius();
	m_v3Center2 = m_BCC2->GetCenter();
	//m_pCube2 = new PrimitiveClass();
	//m_pCube2->GenerateCube(m_fRadius2*2, REGREEN);

	


}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	// find elapsed time
	double deltaTime = m_pSystem->LapClock();

	//First person camera movement
	if (m_bFPC == true)
		CameraRotation();

	ArcBall();

	//Set the model matrices for both objects and Bounding Spheres
	m_pMeshMngr->SetModelMatrix(glm::translate(m_v3O1) * ToMatrix4(m_qArcBall), "Steve");
	m_pMeshMngr->SetModelMatrix(glm::translate(m_v3O2), "Creeper");
	m_BCC1->SetModelMatrix(glm::translate(m_v3O1) * ToMatrix4(m_qArcBall));
	m_BCC2->SetModelMatrix(glm::translate(m_v3O2));
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();
	matrix4 m4View = m_pCameraMngr->GetViewMatrix();

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	vector3 radii = vector3(m_fRadius1x, m_fRadius1y, m_fRadius1z);

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();

	//Collision check goes here
	m_m4Steve = m_pMeshMngr->GetModelMatrix("Steve") * glm::translate(m_v3Center1);
	if (m_BCC1->GetVisibility()) {
		if (m_BCC1->IsColliding(m_BCC2))
			m_pMeshMngr->AddCubeToQueue(m_m4Steve * glm::scale(radii*2.0f), m_BCC1->GetColor(), WIRE);
		else
			m_pMeshMngr->AddCubeToQueue(m_m4Steve * glm::scale(radii*2.0f), m_BCC1->GetColor(), WIRE);
	}
	m_m4Creeper = m_pMeshMngr->GetModelMatrix("Creeper") * glm::translate(m_v3Center2);
	if (m_BCC1->IsColliding(m_BCC2))
		m_pMeshMngr->AddSphereToQueue(m_m4Creeper * glm::scale(vector3(m_fRadius2 * 2.0f)), m_BCC2->GetColor(), WIRE);
	else
		m_pMeshMngr->AddSphereToQueue(m_m4Creeper * glm::scale(vector3(m_fRadius2 * 2.0f)), m_BCC2->GetColor(), WIRE);

	//banana
	m_BOM->CheckCollisions();

	//print info into the console
	printf("FPS: %d            \r", nFPS);//print the Frames per Second

	//Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	if (m_BCC1->IsColliding(m_BCC2))
		m_pMeshMngr->PrintLine("They are colliding! >_<", RERED);
	else
		m_pMeshMngr->PrintLine("They are not colliding! =)", REGREEN);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();

	//Render the grid based on the camera's mode:
	switch (m_pCameraMngr->GetCameraMode())
	{
	default: //Perspective
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY); //renders the XY grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOX:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::YZ, RERED * 0.75f); //renders the YZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOY:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XZ, REGREEN * 0.75f); //renders the XZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOZ:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY, REBLUE * 0.75f); //renders the XY grid with a 100% scale
		break;
	}

	m_pMeshMngr->Render(); //renders the render list

	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	/*if (m_pCube1 != nullptr)
	{
		delete m_pCube1;
		m_pCube1 = nullptr;

	}
	if (m_pCube2 != nullptr)
	{
		delete m_pCube2;
		m_pCube2 = nullptr;

	}*/
	if (m_BCC1 != nullptr)
	{
		delete m_BCC1;
		m_BCC1 = nullptr;

	}
	if (m_BCC2 != nullptr)
	{
		delete m_BCC2;
		m_BCC2 = nullptr;

	}

	super::Release(); //release the memory of the inherited fields
}