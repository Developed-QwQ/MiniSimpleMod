#include "speed.h"

speed::speed() :IModule("Speed", 'M', Category::MOVEMENT, "speed") {
	this->registerFloatSetting("speed", &this->Movespeed, this->Movespeed, 0, 255.f);

}

speed::~speed()
{
}
void speed::onEnable() {
	PlayerAttrib* Playerattrib = Game.getLocalPlayer()->Playerattrib;
	if (auto Localplayer = Game.getLocalPlayer();Localplayer != nullptr) {
		Playerattrib->Jumpheight= Movespeed;
		Playerattrib->Runningspeed= Movespeed;
		Playerattrib->Squatspeed= Movespeed;
		Playerattrib->Speedwater= Movespeed;
	}
}
std::string speed::getModuleName()
{
	return "Speed";
}