#pragma once
#include "../Graphics.h"
#include "../Bindable/ConstantBuffers.h"
#include"Drawable.h"
class PointLight
{
public:
	PointLight(Graphics& gfx);
	void Reset() noexcept;
	void Bind( Graphics& gfx,DirectX::FXMMATRIX view ) const noexcept;
private:
	struct PointLightCBuf
	{
		alignas(16) DirectX::XMFLOAT3 pos;
		alignas(16) DirectX::XMFLOAT3 ambient;
		alignas(16) DirectX::XMFLOAT3 diffuseColor;
		float diffuseIntensity;
		float attConst;
		float attLin;
		float attQuad;
	};
private:
	PointLightCBuf cbData;
	mutable PixelConstantBuffer<PointLightCBuf> cbuf;
};