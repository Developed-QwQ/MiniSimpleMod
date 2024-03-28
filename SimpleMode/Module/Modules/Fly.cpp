#include "Fly.h"

Fly::Fly() :IModule("Fly", 'F', Category::MOVEMENT, "Fly to the sky!") {
	mode.addEntry(EnumEntry("Creative", 0))
		.addEntry(EnumEntry("Jetpack", 1));
	registerEnumSetting("Mode", &mode, 0);
	this->registerFloatSetting("speed", &this->speed, this->speed, 0.f, 64.f);
}

Fly::~Fly()
{
}

void Fly::onEnable()
{
}

std::string Fly::getModuleName()
{
	return "Fly";
}

void Fly::onTick(GameMode* gm)
{
	switch (mode.selected)
	{
	case 0:
		Game.getLocalPlayer()->setFlying(true);
		break;
	case 1:
		break;
	}
}

void Fly::onDisable()
{
}