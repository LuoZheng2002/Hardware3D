#pragma once
#include <Windows.h>
#include <wrl.h>
#include <vector>
#include <dxgidebug.h>
#include <string>
#include"Exception.h"
#include<map>

struct GfxErrorInfo
{
	DXGI_INFO_QUEUE_MESSAGE_CATEGORY category;
	DXGI_INFO_QUEUE_MESSAGE_SEVERITY severity;
	std::string description;
};

class DxgiInfoManager
{
public:
	DxgiInfoManager();
	~DxgiInfoManager() = default;
	DxgiInfoManager(const DxgiInfoManager&) = delete;
	DxgiInfoManager& operator=(const DxgiInfoManager&) = delete;
	std::vector<GfxErrorInfo> GetMessages() const;
public:
	static std::map<DXGI_INFO_QUEUE_MESSAGE_CATEGORY, std::string> categoryToString;
	static std::map<DXGI_INFO_QUEUE_MESSAGE_SEVERITY, std::string> severityToString;
private:
	Microsoft::WRL::ComPtr<IDXGIInfoQueue> pDxgiInfoQueue;
	
};
std::string FormatGfxErrorInfo(const std::vector<GfxErrorInfo>& errors);

#define CHECK_GFX_ERROR if (std::vector<GfxErrorInfo> errors = infoManager.GetMessages(); errors.size() > 0) throw Exception(__LINE__, __FILE__, FormatGfxErrorInfo(errors))
#define INFOMAN(gfx) DxgiInfoManager& infoManager = gfx.infoManager