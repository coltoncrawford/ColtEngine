/////////////////////////////
// Filename: Camera.h
/////////////////////////////

#include <DirectXMath.h>
#include <Windows.h>
#include "InputManager.h"
#pragma once

using namespace DirectX;

class Camera
{
public:
	Camera();
	Camera(const Camera& other);
	~Camera();

	XMFLOAT4X4 GetViewMatrix();
	XMFLOAT4X4 GetProjMatrix();

	void Update(float deltaTime, InputManager* iManager);
	void RotateCamera(int dX, int dY);
	void CalcProjMat(float width, float height);

private:
	float pitch;			// Rotation about X axis
	float yaw;				// Rotation about Y axis
	float speed;			// Camera's translation speed
	XMFLOAT3 position;		// Camera's position
	XMFLOAT3 direction;		// Camera's direction
	XMFLOAT4X4 view;		// View matrix
	XMFLOAT4X4 projection;	// Projection matrix
};

