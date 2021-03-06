/////////////////////////////
// Filename: SystemClass.cpp
/////////////////////////////

#include "SystemClass.h"

SystemClass::SystemClass()
{
	m_Input = 0;
	m_Graphics = 0;
	m_Camera = 0;
}

SystemClass::SystemClass(const SystemClass& other)
{
}

SystemClass::~SystemClass()
{
}

bool SystemClass::Initialize()
{
	// Initialize the screen to 0
	int screenHeight = 0;
	int screenWidth = 0;
	bool result;

	// Initialize the windows api
	InitializeWindows(screenHeight, screenWidth);

	// Create the input object, used to handle keyboard and mouse input
	m_Input = new InputManager();
	if (!m_Input)
	{
		return false;
	}

	// Create the graphics object
	m_Graphics = new GraphicsManager();
	if (!m_Graphics)
	{
		return false;
	}

	m_Camera = new Camera();
	if (!m_Camera)
	{
		return false;
	}

	// Initialize the input object
	m_Input->Initialize();

	// Initialize the graphics object
	m_Graphics->Initialize(screenHeight, screenWidth, m_hwnd);

	return true;
}

void SystemClass::Shutdown()
{
	//Shutdown the window
	ShutdownWindows();

	if (m_Input)
	{
		delete m_Input;
		m_Input = 0;
	}

	if (m_Graphics)
	{
		delete m_Graphics;
		m_Graphics = 0;
	}

	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	return;
}

void SystemClass::Run()
{
	MSG msg;
	bool done, result;

	// Initialize the message structure
	ZeroMemory(&msg, sizeof(MSG));

	// Loop until quit
	done = false;
	while (!done)
	{
		// Handle the windows mesages
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// If windows signals to end then exit out
		if (msg.message == WM_QUIT)
		{
			done = true;
		}
		else
		{
			// Otherwise do frame processing
			result = Update();
			if (!result)
			{
				done = true;
			}
		}
	}

	return;
}

void SystemClass::UpdateTimer()
{
	// Grab the current time
	__int64 now;
	QueryPerformanceCounter((LARGE_INTEGER*)&now);
	currentTime = now;

	// Calculate delta time and clamp to zero
	//  - Could go negative if CPU goes into power save mode 
	//    or the process itself gets moved to another core
	deltaTime = max((float)((currentTime - previousTime) * perfCounterSeconds), 0.0f);

	// Calculate the total time from start to now
	totalTime = (float)((currentTime - startTime) * perfCounterSeconds);

	// Save current time for next frame
	previousTime = currentTime;
}

bool SystemClass::Update()
{
	bool result;

	// Check if ESC is pressed
	if (m_Input->IsKeyDown(VK_ESCAPE))
	{
		return false;
	}
	
	// Do camera update
	m_Camera->Update(deltaTime, m_Input);

	// Do the frame processing for the graphics object
	// might need to pass in camera matrix
	result = m_Graphics->Update(); // From this point everything will draw, make sure eveything is updated before this point
	if (!result)
	{
		return false;
	}

	return true;
}

LRESULT SystemClass::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	switch (umsg)
	{
		// Check if a key has been pressed
		case WM_KEYDOWN:
		{
			// If a key is pressed send it to the input object so it can record that state
			m_Input->KeyDown((unsigned int)wparam);
			return 0;
		}

		// Check if a key has been released
		case WM_KEYUP:
		{
			// If a key is released then send it to the input object so it can unset the state for that key
			m_Input->KeyUp((unsigned int)wparam);
			return 0;
		}

		// Check if the window is being destroyed
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}

		// Check if the window is being closed
		case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}

		// Any other messages send to the default message handler as our application won't make use of them
		default:
		{
			return DefWindowProc(hwnd, umsg, wparam, lparam);
		}
	}
}

void SystemClass::InitializeWindows(int &screenHeight, int & screenWidth)
{
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX, posY;

	// Get an external pointer to this object
	ApplicationHandle = this;

	// Get the instance of this application
	m_hinstance = GetModuleHandle(NULL);

	// Give the application a name
	m_applicationName = L"ColtEngine";

	// Setup the windows class with default settings
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hinstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	// Register the window class
	RegisterClassEx(&wc);

	// Get the screens width and height
	//screenHeight = GetSystemMetrics(SM_CYSCREEN);
	//screenWidth = GetSystemMetrics(SM_CXSCREEN);

	// Setup the screen settings depending on whether it is running in full screen or in windowed mode
	/*if ()
	{
		// If full screen set the screen to maximum size of the users desktop and 32bit
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmPelsWidth = (unsigned long)screenWidth;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Change the display settings to full screen
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		// Set the position of the window to the top left corner
		posX = posY = 0;
	}*/
	//else
	//{
		// If windowed then set it to 800x600 resolution
		screenWidth = 1024;
		screenHeight = 720;

		// Place the window in the middle of the screen
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	//}

	// Create the window with the screen settings and get the handle to it
	m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName, WS_OVERLAPPEDWINDOW, posX, posY, screenWidth, screenHeight, NULL, NULL, m_hinstance, NULL);

	// Bring the window up on the screen and set it as main focus
	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);

	// Hide the mouse cursor
	// ShowCursor(false);

	return;
}

void SystemClass::ShutdownWindows()
{
	// Show the mouse cursor.
	ShowCursor(true);

	// Fix the display settings if leaving full screen mode.
	/*if ()
	{
		ChangeDisplaySettings(NULL, 0);
	}*/

	// Remove the window.
	DestroyWindow(m_hwnd);
	m_hwnd = NULL;

	// Remove the application instance.
	UnregisterClass(m_applicationName, m_hinstance);
	m_hinstance = NULL;

	return;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
		return ApplicationHandle->MessageHandler(hwnd, umessage, wparam, lparam);
}
