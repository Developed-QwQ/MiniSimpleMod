#pragma once
#include <map>
#include <vector>
#include "../../Utils/Logger.h"
#include "css.h"
#include "../Module/Modules/IModule.h"
#include "../../includes/imgui/imgui.h"
#include "../../includes/imgui/imgui_impl_dx11.h"
#include "../../includes/imgui/imgui_impl_win32.h"

class Hub {
private:
	SettingEntry* setting;
	int totalMenuCnt = 7;
public:
	css GetCSS() { return ceses; }
	int CatToOrd(Category c);
private:

	inline  void getModuleListByCategory(Category category, std::vector<std::shared_ptr<IModule>>* modList);

public:
	//static void init();

	void renderCategory(Category category);
	void RenderModSettings(IModule* mod);
	void Renderslidermodsettings(IModule* mod);

	void RenderMenu();
	 void RenderingUI(Category c);
	void DisplayUI(Category c);
	void RenderSettings();
	//static void onKeyUpdate(int key, bool isDown);
	//static void onWheelScroll(bool direction); // true = up, false = down
	//static void onLoadConfig(void* confVoid);
	//static void onSaveConfig(void* confVoid);
};
inline Hub hub = Hub();