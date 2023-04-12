#pragma once
#include"../Graphics.h"
class ShaderBytecode
{
public:
	ShaderBytecode(const std::wstring& path);
	ID3DBlob* Get() const noexcept;
protected:
	Microsoft::WRL::ComPtr<ID3DBlob> pBytecodeBlob;
};
