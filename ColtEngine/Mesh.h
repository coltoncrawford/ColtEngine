/////////////////////////////
// Filename:Mesh.h
/////////////////////////////

#include "Vertex.h"
#include <vector>
#include <fstream>
#include <DirectXMath.h>
#include <d3d11.h>
#pragma once

using namespace DirectX;

class Mesh
{
public:
	Mesh();
	Mesh(const Mesh& other);
	~Mesh();

	bool Initialize(char* fileName, ID3D11Device* device);
	void Shutdown();
	void Render(ID3D11DeviceContext* deviceContext);

	int GetIndexCount();
	int GetVertexCount();
	ID3D11Buffer* GetVertexBuffer();
	ID3D11Buffer* GetIndexBuffer();

private:
	bool InitializeBuffers(Vertex* vertArray, u_int* indicesArray, ID3D11Device* device);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadMesh(char* fileName, ID3D11Device* device);

	// Buffers to hold actual geometry data
	ID3D11Buffer* m_vertexBuffer;
	ID3D11Buffer* m_indexBuffer;

	int m_indexCount;
	int m_vertexCount;
};

