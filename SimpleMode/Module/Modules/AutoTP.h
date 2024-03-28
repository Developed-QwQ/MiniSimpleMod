#pragma once
#include "IModule.h"
#include "../ModManager.h"
class AutoTP :public IModule {
private:
	int  radius = 6;
	int Odelay = 0;
public:
	AutoTP();
	~AutoTP();
//	virtual void onPlayerTick(Player* player) override;
	virtual std::string getModuleName() override;
	virtual void onAttack(ActorBase* actorbase) override;
	//virtual void onTick(GameMode* gm) override;
	//virtual void onEnable() override;
};
