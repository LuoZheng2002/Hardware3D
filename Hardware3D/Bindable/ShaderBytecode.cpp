#include "ShaderBytecode.h"
#include"../Exception.h"

ShaderBytecode::ShaderBytecode(const std::wstring& path)
{
	D3DReadFileToBlob(path.c_str(), &pBytecodeBlob);
	CHECK_WINAPI_ERROR;
}
ID3DBlob* ShaderBytecode::Get() const noexcept
{
	return pBytecodeBlob.Get();
}
