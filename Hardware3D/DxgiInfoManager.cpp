#include "DxgiInfoManager.h"
#include"Exception.h"
#pragma comment(lib, "dxguid.lib")
DxgiInfoManager::DxgiInfoManager()
{
	// define function signature of DXGIGetDebugInterface
	typedef HRESULT(WINAPI* DXGIGetDebugInterface)(REFIID, void**);

	// load the dll that contains the function DXGIGetDebugInterface
	const auto hModDxgiDebug = LoadLibraryEx(TEXT("dxgidebug.dll"), nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
	CHECK_WINAPI_ERROR;

	// get address of DXGIGetDebugInterface in dll
	const auto DxgiGetDebugInterface = reinterpret_cast<DXGIGetDebugInterface>(
		reinterpret_cast<void*>(GetProcAddress(hModDxgiDebug, "DXGIGetDebugInterface"))
		);
	CHECK_WINAPI_ERROR;
	DxgiGetDebugInterface(__uuidof(IDXGIInfoQueue), &pDxgiInfoQueue);
	CHECK_WINAPI_ERROR;
}

std::vector<GfxErrorInfo> DxgiInfoManager::GetMessages() const
{
	std::vector<GfxErrorInfo> messages;
	const auto numMessages = pDxgiInfoQueue->GetNumStoredMessages(DXGI_DEBUG_ALL);
	if (numMessages == 0)
	{
		return {};
	}
	for (auto i = 0; i < numMessages; i++)
	{
		SIZE_T messageLength = 0;
		// get the size of message i in bytes
		pDxgiInfoQueue->GetMessage(DXGI_DEBUG_ALL, i, nullptr, &messageLength);
		// CHECK_WINAPI_ERROR;
		// allocate memory for message
		auto bytes = std::make_unique<byte[]>(messageLength);
		auto pMessage = reinterpret_cast<DXGI_INFO_QUEUE_MESSAGE*>(bytes.get());
		// get the message and push its description into the vector
		pDxgiInfoQueue->GetMessage(DXGI_DEBUG_ALL, i, pMessage, &messageLength);
		// CHECK_WINAPI_ERROR;
		if (pMessage->Severity == DXGI_INFO_QUEUE_MESSAGE_SEVERITY_WARNING && 
			(std::string(pMessage->pDescription).contains("DXGI_SWAP_EFFECT_DISCARD")
				|| std::string(pMessage->pDescription).contains("Constant Buffer")))
		{
			continue;
		}
		messages.emplace_back(pMessage->Category, pMessage->Severity, pMessage->pDescription);
	}
	return messages;
}

std::string FormatGfxErrorInfo(const std::vector<GfxErrorInfo>& errors)
{
	std::string result = "\n\n";
	for (const auto& info : errors)
	{
		std::string infoString = std::format("[Category] {}\n[Severity] {}\n[Description] {}\n", DxgiInfoManager::categoryToString[info.category], DxgiInfoManager::severityToString[info.severity], info.description);
		result += infoString;
	}
	return result;
}
std::map<DXGI_INFO_QUEUE_MESSAGE_CATEGORY, std::string> DxgiInfoManager::categoryToString =
{
	{DXGI_INFO_QUEUE_MESSAGE_CATEGORY_CLEANUP, "Clean Up"},
	{DXGI_INFO_QUEUE_MESSAGE_CATEGORY_COMPILATION, "Compilation"},
	{DXGI_INFO_QUEUE_MESSAGE_CATEGORY_EXECUTION, "Execution"},
	{DXGI_INFO_QUEUE_MESSAGE_CATEGORY_INITIALIZATION, "Initialization"},
	{DXGI_INFO_QUEUE_MESSAGE_CATEGORY_MISCELLANEOUS, "Miscellaneous"},
	{DXGI_INFO_QUEUE_MESSAGE_CATEGORY_RESOURCE_MANIPULATION, "Resource Manipulation"},
	{DXGI_INFO_QUEUE_MESSAGE_CATEGORY_SHADER, "Shader"},
	{DXGI_INFO_QUEUE_MESSAGE_CATEGORY_STATE_CREATION, "State Creation"},
	{DXGI_INFO_QUEUE_MESSAGE_CATEGORY_STATE_GETTING, "State Getting"},
	{DXGI_INFO_QUEUE_MESSAGE_CATEGORY_STATE_SETTING, "State Setting"},
	{DXGI_INFO_QUEUE_MESSAGE_CATEGORY_UNKNOWN, "Unknown"}
};
std::map<DXGI_INFO_QUEUE_MESSAGE_SEVERITY, std::string> DxgiInfoManager::severityToString =
{
		{DXGI_INFO_QUEUE_MESSAGE_SEVERITY::DXGI_INFO_QUEUE_MESSAGE_SEVERITY_CORRUPTION, "Corruption"},
		{DXGI_INFO_QUEUE_MESSAGE_SEVERITY::DXGI_INFO_QUEUE_MESSAGE_SEVERITY_ERROR, "Error"},
		{DXGI_INFO_QUEUE_MESSAGE_SEVERITY::DXGI_INFO_QUEUE_MESSAGE_SEVERITY_INFO, "Info"},
		{DXGI_INFO_QUEUE_MESSAGE_SEVERITY::DXGI_INFO_QUEUE_MESSAGE_SEVERITY_MESSAGE, "Message"},
		{DXGI_INFO_QUEUE_MESSAGE_SEVERITY::DXGI_INFO_QUEUE_MESSAGE_SEVERITY_WARNING, "Warning"}
};