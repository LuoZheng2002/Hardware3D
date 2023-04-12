#pragma once
#include<Windows.h>
#include "Exception.h"
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <wrl.h>
#include <vector>
#include "DxgiInfoManager.h"
namespace wrl = Microsoft::WRL;
namespace dx = DirectX;

class Graphics
{
	friend class Bindable;
public:
	Graphics(HWND hWnd);
	void EndFrame();
	void BeginFrame(float red, float green, float blue);
	void DrawIndexed(UINT count);
	void SetProjection(DirectX::FXMMATRIX proj) noexcept;
	DirectX::XMMATRIX GetProjection() const noexcept;
	void SetCamera(DirectX::FXMMATRIX cam) noexcept;
	DirectX::XMMATRIX GetCamera() const noexcept;
private:
	void CreateDeviceAndSwapChain();
	void CreateRenderTargetView();
	void CreateDepthStencilView();
	void CreateViewport();
public:
#ifndef NDEBUG
	DxgiInfoManager infoManager;
#endif
public:
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext;
private:
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwap;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pTarget;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pDSV;
	HWND hWnd;
	DirectX::XMMATRIX projection;
	DirectX::XMMATRIX camera;
};

