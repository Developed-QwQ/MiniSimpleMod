#include "speed.h"

speed::speed() :IModule("Speed",'M', Category::MOVEMENT, "speed"){
	this->registerFloatSetting("speed", &this->Movespeed, this->Movespeed, 0, 255.f);
}

speed::~speed()
{
}
void speed::onEnable(){
	if (auto Localplayer = Game.getLocalPlayer();Localplayer != nullptr) {
				*reinterpret_cast<float*>(reinterpret_cast<uintptr_t>(Localplayer->Playerattrib) + 0xCC) = Movespeed;
				*reinterpret_cast<float*>(reinterpret_cast<uintptr_t>(Localplayer->Playerattrib) + 0xD0) = Movespeed;
				*reinterpret_cast<float*>(reinterpret_cast<uintptr_t>(Localplayer->Playerattrib) + 0xD4) = Movespeed;
				*reinterpret_cast<float*>(reinterpret_cast<uintptr_t>(Localplayer->Playerattrib) + 0xD8) = Movespeed;
	}
}
const char* speed::getModuleName()
{
	return "Speed";
}