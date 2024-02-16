#include "Airjump.h"
Airjump::Airjump() :IModule("AirJump", 'H', Category::MOVEMENT, "Jump even you're not on the ground.") {
	//this->registerBoolSetting("Airjump", &this->legacyMode, this->legacyMode);
	//this->registerFloatSetting(u8"ÌøÔ¾¼ä¸ô", &this->JumpTime,this->JumpTime, 0.f, 10.f);
}

Airjump::~Airjump()
{
}

void Airjump::onEnable(){
	if (auto Localplayer = Game.getLocalPlayer();Localplayer != nullptr) {
		*reinterpret_cast<bool*>(reinterpret_cast<uintptr_t>(Localplayer->playerlocomotion) + 0xA4) = true;
	}
}

const char* Airjump::getModuleName() {
	return "AirJump";
}

void Airjump::onTick(GameMode* gm) {
	
}