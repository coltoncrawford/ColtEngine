/////////////////////////////
// Filename: GraphicsManager.h
/////////////////////////////

#include <windows.h>
#include "D3DCore.h"
#pragma once

class GraphicsManager
{
public:
	GraphicsManager();
	GraphicsManager(const GraphicsManager&);
	~GraphicsManager();

	bool Initialize(int screenHeight, int screenWidth, HWND hwnd);
	void Shutdown();
	bool Update();

private:
	bool Render();

	D3DCore* m_Direct3D;
};

