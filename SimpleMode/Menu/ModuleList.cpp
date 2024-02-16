#include "ModuleList.h"

ModuleList::ModuleList() :IModule("ModList",'0', Category::VISUAL, "Modeule List!") {
	//this->registerBoolSetting("Modules List", &this->initialized, this->initialized);
}

ModuleList::~ModuleList()
{
}

void ModuleList::onEnable()
{
}

void ModuleList::onDisable()
{
}

const char* ModuleList::getModuleName()
{
	return "";
}