#pragma once
#include<Windows.h>
#include<exception>
#include<format>
#include<string>
class Exception: public std::exception
{
public:
	Exception(int line, const char* file, std::string description);
	const char* what() const noexcept override;
private:
	std::string message;
};

std::string TranslateErrorCode(HRESULT hr);

#define CHECK_WINAPI_ERROR if(HRESULT hr = GetLastError(); hr != ERROR_SUCCESS) throw Exception(__LINE__, __FILE__, TranslateErrorCode(hr))
