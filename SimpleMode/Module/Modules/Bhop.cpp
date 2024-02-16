#include "Bhop.h"

Bhop::Bhop() :IModule("Bhop", '0', Category::MOVEMENT, "Hop around like a bunny!") {
//	this->registerBoolSetting("Hive", &this->hive, this->hive);
//	this->registerFloatSetting("speed", &this->speed, this->speed, 0.1f, 0.8f);
}

Bhop::~Bhop()
{
}

void Bhop::onEnable() {
	auto player = Game.getLocalPlayer();
	if (player == nullptr) return;
}

void Bhop::onDisable()
{
}

void Bhop::onFrame()
{
}

const char* Bhop::getModuleName()
{
	return "Bhop";
}