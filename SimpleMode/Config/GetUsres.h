#pragma once
#include <curl/curl.h>
#include <windows.h>
#include <fstream>
#include <string>
#pragma comment(lib, "libcurl.dll.a")
class GetUsres {
private:
	std::string url = "https://raw.githubusercontent.com/Xiemmmm/SimpleMod-users/main/MIni%20users.txt";
	static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output);
	static std::string ReadGitHubRawFile(const std::string& url);
	static std::string GetComputerHWID();
	static void Getresults(bool results);
public:
	GetUsres();
	~GetUsres();
};

