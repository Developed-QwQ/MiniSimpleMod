#pragma once
#include "../ModManager.h"
#include "IModule.h"
class speed :public IModule
{
private:
	float Movespeed = 10;
public:
	speed();
	~speed();
	virtual void onEnable();
	/*virtual void onTick(GameMode* gm);
	virtual void onDisable();
	virtual void onFrame();*/
	virtual const char* getModuleName();
};
