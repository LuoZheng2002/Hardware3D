#include "VertexShader.h"


VertexShader::VertexShader(Graphics& gfx, const ShaderBytecode& bytecode)
{
	INFOMAN(gfx);
	GetDevice(gfx)->CreateVertexShader(
		bytecode.Get()->GetBufferPointer(),
		bytecode.Get()->GetBufferSize(),
		nullptr,
		&pVertexShader);
	CHECK_GFX_ERROR;
}

void VertexShader::Bind(Graphics& gfx) noexcept
{
	GetContext(gfx)->VSSetShader(pVertexShader.Get(), nullptr, 0u);
}
