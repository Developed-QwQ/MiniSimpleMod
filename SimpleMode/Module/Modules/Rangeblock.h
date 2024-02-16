#pragma once
#include "../ModManager.h"
#include "IModule.h"
class Rangeblock:public IModule{
private:
	int delay = 0;
	int nukerRadius = 4;
	bool veinMiner = false;
	bool autodestroy = true;
public:
	Rangeblock();
	~Rangeblock();

	virtual void onEnable();
	virtual const char* getModuleName();
};

