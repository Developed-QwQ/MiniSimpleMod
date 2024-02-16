#pragma once
#include <iostream>
#include "../ModManager.h"
#include "IModule.h"
class Airjump :public IModule {
private:
	int hasJumped = 0;
	bool legacyMode = false;
	float JumpTime = 0;
public:
	Airjump();
	~Airjump();
	//GameMode* mod;
	virtual void onEnable();
	virtual const char* getModuleName() override;
	virtual void onTick(GameMode* gm) override;
};
