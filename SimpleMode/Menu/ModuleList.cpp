#include "ModuleList.h"
#include "HUB&RGB/ColorH.hpp"
#include "HUB&RGB/TimeH.hpp"
#include "../../includes/imgui/imgui.h"

ModuleList::ModuleList() :IModule("ModList", '0', Category::VISUAL, "Modeule List!") {
}

ModuleList::~ModuleList()
{
}
extern ImVec4* colors;
extern ImFont* font;
void ModuleList::onEnable() {
	ImVec2 winPadding = ImGui::GetStyle().WindowPadding;
	std::vector<std::string>modules;
	float calcHeight = winPadding.y * 2, longestStr = 0, shortestStr;
	for (auto& mod : moduleMgr->moduleList) {
		ImVec2 vec2 = ImGui::CalcTextSize(mod->getModuleName().c_str());
		if (vec2.x > longestStr) longestStr = vec2.x;
		calcHeight += vec2.y;
		modules.push_back(mod->getModuleName().c_str());
	}
	if (modules.size() == 0) return;
	calcHeight += ImGui::GetStyle().ItemSpacing.y * (modules.size() - 1);
	ImGui::SetNextWindowSize({ longestStr + winPadding.x * 2, calcHeight });
	ImGui::PushStyleColor(ImGuiCol_WindowBg, NULL);
	ImGui::Begin("  ", 0, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
	ImGui::PopStyleColor();

	for (int i = 0; i < modules.size(); i++) {
		std::string str = modules.at(i);
		float h, s, v;
		ColorH::RGBtoHSV(0.5, 0.2, 0.6, h, s, v);

	}

	ImGui::End();
}

void ModuleList::onDisable()
{
}

std::string ModuleList::getModuleName()
{
	return "";
}