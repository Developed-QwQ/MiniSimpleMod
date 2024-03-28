#include "Airjump.h"
Airjump::Airjump() :IModule("AirJump", 'H', Category::MOVEMENT, "Jump even you're not on the ground.") {
	//this->registerBoolSetting("Airjump", &this->legacyMode, this->legacyMode);
	//this->registerFloatSetting(u8"ÌøÔ¾¼ä¸ô", &this->JumpTime,this->JumpTime, 0.f, 10.f);
}

Airjump::~Airjump()
{
}

void Airjump::onEnable() {
	if (Game.getLocalPlayer() == nullptr) return;
	PlayerLocoMotion* PlayerLocomotion = Game.getLocalPlayer()->playerlocomotion;
	PlayerLocomotion->onGround = true;
}

std::string Airjump::getModuleName() {
	return "AirJump";
}

void Airjump::onTick(GameMode* gm) {
}