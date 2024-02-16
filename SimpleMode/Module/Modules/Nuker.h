#pragma once
#include "../ModManager.h"
#include "IModule.h"
class Nuker :public IModule {
private:
	int delay = 0;
	int nukerRadius = 4;
	bool veinMiner = false;
	bool autodestroy = false;
public:
	Nuker();
	~Nuker();
	// Inherited via IModule
	virtual void onTick(GameMode* gm) override;
	virtual const char* getModuleName();
};
