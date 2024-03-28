#pragma once
#include "IModule.h"
#include "../ModManager.h"

class Killaura :public IModule
{
private:
	int Odelay = 0;
	int delay = 2;
public:
	bool isMobAura = false;
	int range = 7;

	Killaura();
	~Killaura();

	virtual std::string getModuleName() override;
	virtual void onAttack(ActorBase* actorbase) override;
	//virtual void onTick(GameMode* gm) override;
	//	virtual void onEnable() override;
		//virtual void onSendPacket(Packet* packet) override;
};
