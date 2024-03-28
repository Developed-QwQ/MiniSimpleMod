#include "Guiprogram.h"
#include <set>
#include "../Menu/GuiControls.h"
#include "../../includes/imgui/imgui.h"
void Guiprogram::renderCategory(Category category, IModule* mod) {
		std::vector<SettingEntry*>* settings = mod->getSettings();
		for (auto setting : *settings) {
			if (strcmp(setting->name, "enabled") == 0 || strcmp(setting->name, "keybind") == 0)
				continue;
			if (setting->valueType == BOOL_T) {
				Gui->Checkbox(setting->name, &setting->value->_bool);
			}
			if (mod->isEnabled()) {
				if (setting->valueType == ValueType::ENUM_T|| setting->valueType == ValueType::FLOAT_T|| setting->valueType == ValueType::INT_T) {
					ImGui::BeginChild("##Editor", ImVec2(0, 0), true, ImGuiWindowFlags_NoScrollbar);
					if (setting->valueType == ValueType::ENUM_T) {
						ImGui::Checkbox(setting->name,&setting->minValue->_bool);
					}
					if (setting->valueType == ValueType::FLOAT_T) {
						ImGui::SliderFloat(setting->name, &setting->value->_float, setting->minValue->_float, setting->maxValue->_float);
					}
					if (setting->valueType == ValueType::INT_T) {
						ImGui::SliderInt(setting->name, &setting->value->_int, setting->minValue->_int, setting->maxValue->_int);
					}
					ImGui::EndChild();
				}
			}
		}
}
inline void Guiprogram::getModuleListByCategory(Category category, std::vector<std::shared_ptr<IModule>>* modList) {
	auto lock = moduleMgr->lockModuleList();
	std::vector<std::shared_ptr<IModule>>* moduleList = moduleMgr->getModuleList();

	for (auto& it : *moduleList) {
		if (it->getCateg() == category)
			modList->push_back(it);
	}
}
void Guiprogram::render(Category mod) {
  //  renderCategory(mod);
}
Guiprogram* HUB = new Guiprogram();