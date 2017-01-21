/////////////////////////////
// Filename: GraphicsManager.cpp
/////////////////////////////

#include "GraphicsManager.h"

GraphicsManager::GraphicsManager()
{
	m_Direct3D = 0;
}

GraphicsManager::GraphicsManager(const GraphicsManager &)
{
}

GraphicsManager::~GraphicsManager()
{
}

bool GraphicsManager::Initialize(int screenHeight, int screenWidth, HWND hwnd)
{
	bool result;

	// Create the D3D object
	m_Direct3D = new D3DCore();
	if (!m_Direct3D)
	{
		return false;
	}

	// Initialize the D3D object
	result = m_Direct3D->Initialize(screenHeight, screenWidth, hwnd, false, false, 1000.0f, 0.1f);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);
		return false;
	}

	return true;
}

void GraphicsManager::Shutdown()
{
	// Release the D3D object
	if (m_Direct3D)
	{
		m_Direct3D->Shutdown();
		delete m_Direct3D;
		m_Direct3D = 0;
	}
}

bool GraphicsManager::Update()
{
	bool result;

	// Maybe sort objects here first, then continue, or not
	// not sure which would be best

	// Render the scene
	result = Render();
	if (!result)
	{
		return false;
	}
	
	return true;
}

bool GraphicsManager::Render()
{
	// Clear the buffers to begin the scene
	m_Direct3D->BeginScene(0.4f, 0.6f, 0.75f, 0.0f);

	// pass in entity list / any other objects that need to be drawn (skybox, etc.)
	// sort through entities for optimized rendering / draw in correct order
	// loop through what needs to be drawn setting the proper materials/shaders/etc. only when needed
	// context->drawindexed

	// Present the rendered scene to the screen
	m_Direct3D->EndScene();

	return true;
}
