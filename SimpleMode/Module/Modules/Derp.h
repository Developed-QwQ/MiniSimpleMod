#pragma once
#include "../ModManager.h"
#include "IModule.h"
class Derp :public IModule {
private:
	int counter = 0;
	bool packetMode = false;
	double Size = 1.f;
public:
	Derp();
	~Derp();
	GameData Game;
	virtual void onEnable();
	virtual void onDisable();
	virtual void onFrame();
	virtual std::string getModuleName();
};
