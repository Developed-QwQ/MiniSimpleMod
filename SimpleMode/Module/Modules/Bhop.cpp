#include "Bhop.h"

Bhop::Bhop() :IModule("Bhop", '0', Category::MOVEMENT, "Hop around like a bunny!") {
	//	this->registerBoolSetting("Hive", &this->hive, this->hive);
	mode.addEntry(EnumEntry("Creative", 0))
		.addEntry(EnumEntry("Jetpack", 1));
	this->registerEnumSetting("Mode", &mode, 0);
	this->registerFloatSetting("speed", &this->speed, this->speed, 0.1f, 0.8f);

}

Bhop::~Bhop()
{
}

void Bhop::onEnable() {
//	Game.getLocalPlayer()->GetGameObject();


}

void Bhop::onDisable()
{
}

void Bhop::onFrame()
{
}

std::string Bhop::getModuleName()
{
	return "Bhop";
}