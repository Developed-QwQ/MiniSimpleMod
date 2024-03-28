#pragma once
#include "IModule.h"
#include "../ModManager.h"
class Scaffold:public IModule
{
private:

public:
	Scaffold();
	~Scaffold();

	virtual std::string getModuleName() override;
	virtual void onEnable();
};

