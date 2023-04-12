#pragma once
#include "Bindable.h"
#include"ShaderBytecode.h"
class PixelShader : public Bindable
{
public:
	PixelShader(Graphics& gfx, const ShaderBytecode& path);
	void Bind(Graphics& gfx) noexcept override;
protected:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;
};
