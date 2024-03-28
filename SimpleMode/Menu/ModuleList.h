#pragma once
#include <string>
#include <vector>
#include <typeinfo>
#include "../Module/Modules/IModule.h"
#include "../Module/ModManager.h"

class ModuleList :public IModule {
private:
	//ImVec4* colML, * colML_Bg;
	//bool isMLRainbow = true;
public:
	ModuleList();
	~ModuleList();

	virtual void onEnable();
	virtual void onDisable();
	virtual std::string getModuleName();
};
