#pragma once
#include "../../../Utils/logger.h"
#include "IModule.h"
#include "../ModManager.h"
class D3DEsp :public IModule {
private:
	bool Enable = false;
public:
	D3DEsp();
	~D3DEsp();

	//virtual void onEnable();
	//virtual void onDisable();
	virtual std::string getModuleName();
};
