#include "D3DEsp.h"
#include "../../../includes/kiero/kiero.h"

D3DEsp::D3DEsp() :IModule("D3DEsp", '0', Category::VISUAL, u8"��ʵ����ɫ,���ҿ�������ǽ����ʾ") {
}

D3DEsp::~D3DEsp()
{
}
std::string D3DEsp::getModuleName()
{
	return "D3dEsp";
}