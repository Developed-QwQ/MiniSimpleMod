#include "Derp.h"

Derp::Derp() :IModule("Derp", '0', Category::MISC, "0")
{
	//	this->registerBoolSetting("Derp", &this->packetMode, this->packetMode);
		//   ImGui::SameLine();
}

Derp::~Derp()
{
}

void Derp::onEnable() {
	ActorBody* Actorbody = Game.getLocalPlayer()->Actorbody;
	if (auto Localplayer = Game.getLocalPlayer();Localplayer != nullptr) {
		Actorbody->angle = counter * 2;
		Actorbody->trueangle = counter * 2;
		Actorbody->Lockangle = PI/(counter / Actorbody->Lockangle);
	}
	if (counter < 360)
		counter++;
	else
		counter = 0;
}

void Derp::onDisable()
{
}

void Derp::onFrame()
{
}

std::string Derp::getModuleName()
{
	return "Derp";
}