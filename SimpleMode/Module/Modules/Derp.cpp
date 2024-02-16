#include "Derp.h"

Derp::Derp() :IModule("Derp",'0', Category::MISC, "0")
{
//	this->registerBoolSetting("Derp", &this->packetMode, this->packetMode);
	//   ImGui::SameLine();
}

Derp::~Derp()
{
}

void Derp::onEnable(){
	if (auto Localplayer = Game.getLocalPlayer();Localplayer != nullptr) {
			*reinterpret_cast<float*>(reinterpret_cast<uintptr_t>(Localplayer->Actorbody) + 0x50) = counter * 2;
			*reinterpret_cast<float*>(reinterpret_cast<uintptr_t>(Localplayer->Actorbody) + 0x54) = counter * 2;
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

const char* Derp::getModuleName()
{
	return "Derp";
}