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

bool GraphicsManager::Frame()
{
	bool result;

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
	bool result;

	// Use the D3D object to render
	result = m_Direct3D->Render();
	if (!result)
	{
		return false;
	}

	return true;
}
