#include "ESP.h"

ESP::ESP() :IModule("ESP", 'o', Category::VISUAL, "Makes it easier to find entities around you.") {
}

ESP::~ESP()
{
}

std::string ESP::getModuleName()
{
	return "ESP";
}
void doRenderStuff(ActorBase* ent, bool isRegularEntity) {
	static auto espMod = moduleMgr->getModule<ESP>();
	LocalPlayer* localPlayer = Game.getLocalPlayer();
	if (ent == localPlayer)
		return;
	if (ent->isDead()) return;
}
static float rcolors[4];
void ESP::onTick(GameMode* gm)
{	
	LocalPlayer* localPlayer = Game.getLocalPlayer();
	if (localPlayer != nullptr) {
		// Rainbow colors
		if (rcolors[3] < 1) {
			rcolors[0] = 0.2f;
			rcolors[1] = 0.2f;
			rcolors[2] = 1.f;
			rcolors[3] = 1;
		}
		Game.forEachEntity(doRenderStuff);
	}
}