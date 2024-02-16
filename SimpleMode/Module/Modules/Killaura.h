#pragma once
#include "IModule.h"
#include "../ModManager.h"

class Killaura:public IModule
{
private:
public:
	bool isMobAura = false;
	float range = 6;

	Killaura();
	~Killaura();

	virtual const char* getModuleName() override;
	virtual void onTick(GameMode* gm) override;
	virtual void onEnable() override;
	//virtual void onSendPacket(Packet* packet) override;
};

