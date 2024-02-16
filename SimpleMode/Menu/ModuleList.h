#pragma once
#include <string>
#include <vector>
#include <typeinfo>
#include <optional>
#include <memory>
#include <mutex>
#include <shared_mutex>
#include "../Module/Modules/IModule.h"

#include "../Module/Modules/Derp.h"
#include "../Module/Modules/Airjump.h"
#include "../Module/Modules/speed.h"
class ModuleList :public IModule {
private:
	bool initialized = true;
public:

	ModuleList();
	~ModuleList();
	virtual void onEnable();
	virtual void onDisable();
	virtual const char* getModuleName();
};
