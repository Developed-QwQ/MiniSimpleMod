#include "UserManager.h"
#include "../../Utils/logger.h"
#include <intrin.h> // For __cpuid
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <iphlpapi.h>
#include <fstream>
#include <windows.h>
#include <curl/curl.h>
#include <d3d11.h>
#include <dxgi.h>

#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "cryptlib.lib")
#pragma comment(lib, "libcurl.dll.a")
#pragma comment(lib, "iphlpapi.lib ")
#pragma comment(lib, "Advapi32.lib") // For GetComputerNameA
#pragma comment(lib, "wbemuuid.lib")
#include <aes.h>
#include <modes.h>
#include <filters.h>
using namespace CryptoPP;
size_t UserManager::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
	size_t totalSize = size * nmemb;
	output->append(static_cast<char*>(contents), totalSize);
	return totalSize;
}


std::string UserManager::Userencrypt(std::vector<std::string>* plaintext){
	byte key[AES::DEFAULT_KEYLENGTH];
	memset(key, 0x00, AES::DEFAULT_KEYLENGTH);
	byte iv[AES::BLOCKSIZE];
	memset(iv, 0x00, AES::BLOCKSIZE);

	std::string ciphertext;{
		CBC_Mode<AES>::Encryption encryptor(key, AES::DEFAULT_KEYLENGTH, iv);
		for (auto& str : *plaintext) {
			std::string encryptedString;
			StringSource(str, true, new StreamTransformationFilter(encryptor, new StringSink(encryptedString)));
			str = encryptedString; // 将每个字符串的加密结果追加到总的密文中
		}
	}
	return ciphertext;
}

std::string UserManager::ReadGitHubRawFile(const std::string& url) {
	std::string fileContent;
	CURL* curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &fileContent);
		CURLcode res = curl_easy_perform(curl);
		LOG_INFO("获取user {%s}", (res != CURLE_OK) ? "失败" : "成功");
		curl_easy_cleanup(curl);
	}
	return fileContent;

}

std::string UserManager::GetDiskSerialNumber(){
	DWORD hdd_serial{};
	if (GetVolumeInformationA("C:\\", NULL, NULL,
		&hdd_serial, NULL, NULL, NULL, NULL) == 0) {
		LOG_ERROR("Error encounters 'GetVolumeInformation: ");
	}
	
	std::stringstream ss;
	ss << std::hex << hdd_serial;
	return ss.str();
}

D3DADAPTER_IDENTIFIER9* UserManager::GetgpuID() const{
	IDirect3D9* d9object = Direct3DCreate9(D3D_SDK_VERSION);
	unsigned int adaptercount = d9object->GetAdapterCount();
	D3DADAPTER_IDENTIFIER9* adapters = new D3DADAPTER_IDENTIFIER9[sizeof(adaptercount)];
	for (unsigned int i = 0; i < adaptercount; i++) {
		d9object->GetAdapterIdentifier(i, 0, &(adapters[i]));
	}
	return adapters;
}

std::string UserManager::GetComputername()
{
	return std::string();
}

std::string UserManager::GetMacAddress(){ //获取MAC地址
	std::string macAddress;
	IP_ADAPTER_INFO adapterInfo[16];
	DWORD bufferSize = sizeof(adapterInfo);
	DWORD result = GetAdaptersInfo(adapterInfo, &bufferSize);
	if (result == ERROR_SUCCESS) {
		IP_ADAPTER_INFO* adapter = adapterInfo;
		while (adapter) {
			for (UINT i = 0; i < adapter->AddressLength; i++) {
				std::stringstream ss;
				ss << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<int>(adapter->Address[i]);
				macAddress += ss.str();
			}
			adapter = adapter->Next;
		}
	}
	return macAddress;
}

std::string UserManager::GetCPUID(){//获取CPU ID
	std::string cpu_id;
	int cpu_info[4] = { 0, 0, 0, 0 };
	__cpuid(cpu_info, 0);
	std::ostringstream stream;
	stream << std::hex << cpu_info[1];
	stream << std::hex << cpu_info[3];
	stream << std::hex << cpu_info[2];
	stream << std::hex << cpu_info[0];
	cpu_id = stream.str();
	return cpu_id;
}

void UserManager::getSimpleUser(){
    std::string fileContent = ReadGitHubRawFile(url);
	user.push_back(GetCPUID());
	user.push_back(GetMacAddress());
	Userencrypt(&user);
	std::ofstream hwid("Hwid_.txt");
	if (hwid.is_open()) {
		for (auto& id: user) {
			hwid << id;
			LOG_DEBUG("Hwid%s",id);
		}
		hwid.close();
		LOG_INFO("hwid {Yes}");
	}

    std::ofstream outputFile("MiniSimpleMod_user.txt");
    if (outputFile.is_open()) {
        outputFile << fileContent;
        outputFile.close();
        LOG_INFO("MiniSimpleUsers {Yes}");
    }
}
UserManager::~UserManager(){
    for (auto& clear : user) { clear= " ";}
    user.clear();
}

UserManager* user = new UserManager;