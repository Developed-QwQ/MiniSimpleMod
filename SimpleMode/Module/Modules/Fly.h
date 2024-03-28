#pragma once
#include "IModule.h"
#include "../ModManager.h"
class Fly :public IModule
{
private:
	float speed = 1.f;
public:
	Fly();
	~Fly();

	SettingEnum mode = SettingEnum(this);

	// Inherited via IModule
	virtual void onEnable() override;
	virtual std::string getModuleName() override;
	virtual void onTick(GameMode* gm) override;
	virtual void onDisable() override;
	//virtual void onMove(MoveInputHandler* input) override;
};
