#pragma once

#include "IModule.h"
#include "../ModManager.h"
class ESP :public IModule {
public:
	bool isMobEsp = false;
	bool doRainbow = true;
	bool is2d = false;
	ESP();
	~ESP();

	// Inherited via IModule
	virtual std::string getModuleName() override;
	virtual void onTick(GameMode* gm) override;
};
