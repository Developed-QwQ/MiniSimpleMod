#pragma once
#include <iostream>
#include "../ModManager.h"
#include "IModule.h"
class Bhop :public IModule {
private:
	float speed = 0.325f;
	bool hive = false;
	float speedFriction = 0.65f;
	float cashedStepHeignt = 0.5f;
public:
	Bhop();
	~Bhop();

	GameData Game;
	virtual void onEnable();
	virtual void onDisable();
	virtual void onFrame();
	virtual const char* getModuleName();
};