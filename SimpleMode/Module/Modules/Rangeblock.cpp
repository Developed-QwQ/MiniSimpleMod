#include "Rangeblock.h"

Rangeblock::Rangeblock():IModule(u8"范围放置",'0',Category::WORLD,u8"让你可以放置多个块！"){
}

Rangeblock::~Rangeblock()
{
}

void Rangeblock::onEnable()
{
}

const char* Rangeblock::getModuleName()
{
	return u8"范围放置";
}

