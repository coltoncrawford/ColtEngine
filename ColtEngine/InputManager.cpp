/////////////////////////////
// Filename: InputManager.cpp
/////////////////////////////

#include "InputManager.h"

InputManager::InputManager()
{
}

InputManager::InputManager(const InputManager &)
{
}

InputManager::~InputManager()
{
}

void InputManager::Initialize()
{
	// Initialize all keys to be releaseed
	for (int i = 0; i < 256; ++i)
	{
		m_keys[i] = false;
	}

	return;
}

void InputManager::KeyDown(unsigned int input)
{
	// If a key is pressed then save the state
	m_keys[input] = true;
	return;
}

void InputManager::KeyUp(unsigned int input)
{
	// If a key is released then sace the state
	m_keys[input] = false;
	return;
}

bool InputManager::IsKeyDown(unsigned int key)
{
	// Return the state of a key
	return m_keys[key];
}
