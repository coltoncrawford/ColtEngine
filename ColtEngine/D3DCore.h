/////////////////////////////
// Filename: D3DCore.h
/////////////////////////////

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

// Need to change target platform to Windows 10 for DX12
#include <d3d12.h>
#include <dxgi1_4.h>
#pragma once

class D3DCore
{
public:
	D3DCore();
	D3DCore(const D3DCore&);
	~D3DCore();

	bool Initialize(int, int, HWND, bool, bool, float, float);
	void Shutdown();

	bool Render();

private:
	bool m_vsync_enabled;
	float m_screenDepth, m_screenNear;
	int m_videoCardMemory;
	ID3D12Device* m_device;
	ID3D12CommandQueue* m_commandQueue;
	char m_videoCardDescription[128];
	IDXGISwapChain3* m_swapChain;
	ID3D12DescriptorHeap* m_renderTargetViewHeap;
	ID3D12Resource* m_backBufferRenderTarget[2];
	unsigned int m_bufferIndex;
	ID3D12CommandAllocator* m_commandAllocator;
	ID3D12GraphicsCommandList* m_commandList;
	ID3D12PipelineState* m_pipelineState;
	ID3D12Fence* m_fence;
	HANDLE m_fenceEvent;
	unsigned long long m_fenceValue;
};

