#include "Rangeblock.h"

Rangeblock::Rangeblock() :IModule(u8"��Χ����", '0', Category::WORLD, u8"������Է��ö���飡") {
}

Rangeblock::~Rangeblock()
{
}

void Rangeblock::onEnable() {
}

std::string Rangeblock::getModuleName()
{
	return u8"��Χ����";
}