#pragma once
#include <Windows.h>

#include <filesystem>
#include <fstream>
#include <string>
#pragma comment(lib, "runtimeobject")

#include "../../Utils/Json.hpp"
#include "../Module/ModManager.h"

using json = nlohmann::json;

class ConfigManager{
private:
	std::wstring roamingFolder;
	static std::wstring GetRoamingFolderPath();
	json currentConfigObj;

public:
	ConfigManager();
	~ConfigManager();

	std::string currentConfig = "default";

	void loadConfig(std::string name, bool create);
	void saveConfig();
	void init();
};
extern ConfigManager* configMgr;

