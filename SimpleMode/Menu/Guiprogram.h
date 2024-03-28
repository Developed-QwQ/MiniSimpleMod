#pragma once

#include <map>
#include <vector>
#include "../../Memory/GameData.h"
#include "../Module/ModManager.h"
#include "../Module/Modules/IModule.h"
class Guiprogram{
private:
	int totalMenuCnt = 7;
	float padding = 90.f;
	float height = 38.f;
private:

	inline static void getModuleListByCategory(Category category, std::vector<std::shared_ptr<IModule>>* modList);
	inline static const char* catToName(Category cat) {
		const char* categoryName="";
		{
			switch (cat) {
			case Category::COMBAT:
				categoryName = "Combat";
				break;
			case Category::VISUAL:
				categoryName = "Visual";
				break;
			case Category::MOVEMENT:
				categoryName = "Movement";
				break;
			case Category::PLAYER:
				categoryName = "Player";
				break;
			case Category::WORLD:
				categoryName = "World";
				break;
			case Category::MISC:
				categoryName = "Misc";
				break;
			case Category::CLIENT:
				categoryName = "Client";
				break;
			}
		}
		return categoryName;
	}
public:
	static void renderCategory(Category category, IModule* mod);
	static void render(Category mod);

};

extern Guiprogram* HUB;