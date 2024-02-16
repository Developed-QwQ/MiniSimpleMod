#include "GetUsres.h"
#include "../../Utils/logger.h"
#include <intrin.h> // For __cpuid
#pragma comment(lib, "Advapi32.lib") // For GetComputerNameA

size_t GetUsres::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output){
    size_t totalSize = size * nmemb;
    output->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

std::string GetUsres::ReadGitHubRawFile(const std::string& url){
    std::string fileContent;

    CURL* curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        CURLcode res = curl_easy_perform(curl);
        LOG_INFO("用户获取 {%s}", (res!= CURLE_OK)?"失败":"成功");
        Getresults(false);
        curl_easy_cleanup(curl);
    }

    return fileContent;
}

std::string GetUsres::GetComputerHWID(){
    std::string hwid;
    char computerName[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD computerNameSize = sizeof(computerName) / sizeof(computerName[0]);
    if (GetComputerNameA(computerName, &computerNameSize)) {
        hwid += computerName;
    }
    int cpuInfo[4] = { 0 };
    __cpuid(cpuInfo, 1);
    char processorID[17];
    snprintf(processorID, sizeof(processorID), "%08X%08X", cpuInfo[3], cpuInfo[0]);
    hwid += processorID;
    return hwid;
}

void GetUsres::Getresults(bool results){
    if(!results) ExitThread(0);
}

GetUsres::GetUsres(){
    std::string fileContent = ReadGitHubRawFile(url);
    std::string hwid = GetComputerHWID();

    std::ofstream outputFile("MiniSimpleUsers.txt");
    if (outputFile.is_open()) {
        outputFile << fileContent;
        outputFile.close();
        LOG_INFO("MiniSimpleUsers {Yes}");
    }
}

GetUsres::~GetUsres()
{
}
