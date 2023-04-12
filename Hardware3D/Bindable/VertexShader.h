#pragma once
#include "Bindable.h"
#include"ShaderBytecode.h"
class VertexShader : public Bindable
{
public:
	VertexShader(Graphics& gfx, const ShaderBytecode& bytecode);
	void Bind(Graphics& gfx) noexcept override;
protected:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;
};