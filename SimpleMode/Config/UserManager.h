#pragma once

#include <string>
#include <vector>
#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")

class UserManager {
private:
	std::vector<std::string>user;
	std::string url = "https://gitee.com/brilliant-xiaomi/simple-mode/raw/master/MinSimpleMode";
	static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output);
public:
	 std::string Userencrypt(std::vector<std::string>*plaintext);
	 std::string ReadGitHubRawFile(const std::string& url);
	 std::string GetDiskSerialNumber();
	 D3DADAPTER_IDENTIFIER9* GetgpuID()const;
	 std::string GetProcessorID();
	 std::string GetComputername();
	 std::string GetBiosVersion();
	 std::string GetMacAddress();
	 std::string GetCPUID();
	 void getSimpleUser();

	~UserManager();
};
extern UserManager* user;