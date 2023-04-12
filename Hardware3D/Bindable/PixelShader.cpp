#include "PixelShader.h"

PixelShader::PixelShader(Graphics& gfx, const ShaderBytecode& bytecode)
{
	INFOMAN(gfx);
	GetDevice(gfx)->CreatePixelShader(
		bytecode.Get()->GetBufferPointer(),
		bytecode.Get()->GetBufferSize(),
		nullptr, &pPixelShader);
	CHECK_GFX_ERROR;
}

void PixelShader::Bind(Graphics& gfx) noexcept
{
	GetContext(gfx)->PSSetShader(pPixelShader.Get(), nullptr, 0u);
}
