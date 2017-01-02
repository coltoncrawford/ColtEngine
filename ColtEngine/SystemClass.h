/////////////////////////////
// Filename: SystemClass.h
/////////////////////////////

#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "InputManager.h"
#include "GraphicsManager.h"

class SystemClass
{
public:
	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

	SystemClass();
	SystemClass(const SystemClass&);
	~SystemClass();

	bool Initialize();
	void Shutdown();
	void Run();

private:
	LPCWSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;

	InputManager* m_Input;
	GraphicsManager* m_Graphics;

	bool Frame();
	void InitializeWindows(int&, int&);
	void ShutdownWindows();
};

// These are global for handling windows OS-level messages
static SystemClass* ApplicationHandle = 0;
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


