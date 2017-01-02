/////////////////////////////
// Filename: InputManager.h
/////////////////////////////

#pragma once

class InputManager
{
public:
	InputManager();
	InputManager(const InputManager&);
	~InputManager();

	void Initialize();

	void KeyDown(unsigned int input);
	void KeyUp(unsigned int input);

	bool IsKeyDown(unsigned int key);

private:
	bool m_keys[256];
};

