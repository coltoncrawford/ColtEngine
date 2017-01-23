/////////////////////////////
// Filename: SystemClass.h
/////////////////////////////

#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "InputManager.h"
#include "GraphicsManager.h"
#include "Camera.h"

class SystemClass
{
public:
	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

	SystemClass();
	SystemClass(const SystemClass& other);
	~SystemClass();

	bool Initialize();
	void Shutdown();
	void Run();

private:
	LPCWSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;

	// Timing related data
	double perfCounterSeconds;
	float totalTime;
	float deltaTime;
	__int64 startTime;
	__int64 currentTime;
	__int64 previousTime;

	InputManager* m_Input;
	GraphicsManager* m_Graphics;
	Camera* m_Camera;

	void UpdateTimer();
	bool Update();
	void InitializeWindows(int &screenHeight, int & screenWidth);
	void ShutdownWindows();
};

// These are global for handling windows OS-level messages
static SystemClass* ApplicationHandle = 0;
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


