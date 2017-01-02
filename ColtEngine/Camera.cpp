/////////////////////////////
// Filename: Camera.cpp
/////////////////////////////

#include "Camera.h"

Camera::Camera()
{
	position = XMFLOAT3(0.0f, 0.0f, -5.0f);
	direction = XMFLOAT3(0.0f, 0.0f, 1.0f);
	pitch = 0.0f;
	yaw = 0.0f;
	speed = 10.0f;
}

Camera::Camera(const Camera &)
{
}

Camera::~Camera()
{
}

XMFLOAT4X4 Camera::GetViewMatrix()
{
	return view;
}

XMFLOAT4X4 Camera::GetProjMatrix()
{
	return projection;
}

void Camera::Update(float deltaTime, InputManager* iManager)
{
	// Calculate rotation quaternion, forward vector
	XMVECTOR rotationQuat = XMQuaternionRotationRollPitchYaw(pitch, yaw, 0.0f);
	XMVECTOR rotatedForward = XMVector3Rotate(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), rotationQuat);

	// Calculate right vector to be used for input
	XMVECTOR rightVector = XMVector3Cross(rotatedForward, XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));

	// Calculate view matrix
	XMMATRIX viewMat = XMMatrixLookToLH(XMLoadFloat3(&position), rotatedForward, XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));

	// MARK: UPDATE CAMERA POS BASED OFF OF INPUT
	#pragma region Update camera pos based off of input

	// Forward + Backward
	if (iManager->IsKeyDown(0x57))	// W
	{
		XMStoreFloat3(&position, XMLoadFloat3(&position) + (rotatedForward * speed * deltaTime));
	}
	if (iManager->IsKeyDown(0x53))	// S
	{
		XMStoreFloat3(&position, XMLoadFloat3(&position) - (rotatedForward * speed * deltaTime));
	}

	// Left + Right
	if (iManager->IsKeyDown(0x41))	// A
	{
		XMStoreFloat3(&position, XMLoadFloat3(&position) + (rightVector * speed * deltaTime));
	}
	if (iManager->IsKeyDown(0x44))	// D
	{
		XMStoreFloat3(&position, XMLoadFloat3(&position) - (rightVector * speed * deltaTime));
	}

	// Up + Down
	if (iManager->IsKeyDown(VK_SPACE))
	{
		position.y += speed * deltaTime;
	}
	if (iManager->IsKeyDown(0x58))	// X
	{
		position.y -= speed * deltaTime;
	}
	#pragma endregion

	// Store variables to member safe data types
	XMStoreFloat3(&direction, rotatedForward);
	XMStoreFloat4x4(&view, XMMatrixTranspose(viewMat));
}

void Camera::RotateCamera(int dX, int dY)
{
	pitch += (dY / 150.0f);
	if (pitch > 3.14159 / 2) {
		pitch = 3.14159 / 2;
	}
	else if (pitch < -3.14159 / 2) {
		pitch = -3.14159 / 2;
	}
	yaw += (dX / 150.0f);
	if (yaw > 3.14159) {
		yaw = -3.14159;
	}
	else if (yaw < -3.14159) {
		yaw = 3.14159;
	}
}

void Camera::CalcProjMat(float width, float height)
{
	// Create the Projection matrix
	// - This should match the window's aspect ratio, and also update anytime
	//   the window resizes (which is already happening in OnResize() below)
	XMMATRIX projMat = XMMatrixPerspectiveFovLH(
		0.25f * 3.1415926535f,		// Field of View Angle
		(float)width / height,		// Aspect ratio
		0.1f,						// Near clip plane distance
		100.0f);					// Far clip plane distance
	XMStoreFloat4x4(&projection, XMMatrixTranspose(projMat)); // Transpose for HLSL!
}
