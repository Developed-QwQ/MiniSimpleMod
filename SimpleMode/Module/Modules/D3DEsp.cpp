#include "D3DEsp.h"
#include "../../../includes/kiero/kiero.h"

D3DEsp::D3DEsp() :IModule("D3DEsp", '0', Category::VISUAL, u8"给实体上色,并且可以无视墙体显示") {
}

D3DEsp::~D3DEsp()
{
}
std::string D3DEsp::getModuleName()
{
	return "D3dEsp";
}