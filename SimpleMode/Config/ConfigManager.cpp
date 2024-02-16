#include "ConfigManager.h"
#include <windows.storage.h>
#include <wrl.h>

using namespace ABI::Windows::Storage;
using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;

std::wstring ConfigManager::GetRoamingFolderPath(){
	ComPtr<IApplicationDataStatics> appDataStatics;
	auto hr = RoGetActivationFactory(HStringReference(L"Windows.Storage.ApplicationData").Get(), __uuidof(appDataStatics), &appDataStatics);
	if (FAILED(hr)) throw std::runtime_error("Failed to retrieve application data statics");

	ComPtr<IApplicationData> appData;
	hr = appDataStatics->get_Current(&appData);
	if (FAILED(hr)) throw std::runtime_error("Failed to retrieve current application data");

	ComPtr<IStorageFolder> roamingFolder;
	hr = appData->get_RoamingFolder(&roamingFolder);
	if (FAILED(hr)) throw std::runtime_error("Failed to retrieve roaming folder");

	ComPtr<IStorageItem> folderItem;
	hr = roamingFolder.As(&folderItem);
	if (FAILED(hr)) throw std::runtime_error("Failed to cast roaming folder to IStorageItem");

	HString roamingPathHString;
	hr = folderItem->get_Path(roamingPathHString.GetAddressOf());
	if (FAILED(hr)) throw std::runtime_error("Failed to retrieve roaming folder path");

	uint32_t pathLength;
	auto roamingPathCStr = roamingPathHString.GetRawBuffer(&pathLength);
	return std::wstring(roamingPathCStr, pathLength);
}

ConfigManager::ConfigManager()
{
	roamingFolder = GetRoamingFolderPath();
}
ConfigManager::~ConfigManager(){}
void ConfigManager::loadConfig(std::string name, bool create)
{
}

void ConfigManager::saveConfig(){
	LOG_INFO("Saving config %s", currentConfig.c_str());
	size_t allocSize = currentConfig.size() + roamingFolder.size() + 20;  // std::wstring::size() can be weird so lets make sure this actually fits
	char* fullPath = new char[allocSize];
	sprintf_s(fullPath, allocSize, "%S\\%s.h", roamingFolder.c_str(), currentConfig.c_str());

	moduleMgr->onSaveConfig(&currentConfigObj);

	std::string prefix;
//	prefix.push_back(cmdMgr->prefix);
	//currentConfigObj["prefix"] = prefix;
	//currentConfigObj["friends"] = friends.getList();

	std::ofstream o(fullPath, std::ifstream::binary);
	o << std::setw(4) << currentConfigObj << std::endl;
	o.flush();
	o.close();

	delete[] fullPath;
}

void ConfigManager::init()
{
	LOG_INFO("Initializing config...");
	loadConfig(currentConfig, true);
}
ConfigManager* configMgr = new ConfigManager();