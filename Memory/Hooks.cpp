#include <windows.h>
#include <algorithm>
#include "../Utils/logger.h"
#include "../includes/glm/glm/ext/matrix_clip_space.hpp"
#include "../includes/glm/glm/ext/matrix_relational.hpp"
#include "../includes/glm/glm/ext/matrix_transform.hpp"
#include "../includes/glm/glm/gtc/constants.hpp"
#include "../includes/glm/glm/mat4x4.hpp"
#include "../includes/glm/glm/trigonometric.hpp"
#include "../Utils/Utils.h"
#include "Hooks.h"
using namespace std;

Hooks g_Hooks;
void Hooks::Init() {
	LOG_INFO("Setting up Hooks...");
	{
		uintptr_t Localplayer = FindSignature("56 8B F1 E8 ? ? ? ? 85 C0 74 2F 8B C8 E8 ? ? ? ? 6A 00 68 ? ? ? ? 68 ? ? ? ? 6A 00 50 E8 ? ? ? ? 8B C8 83 C4 14 85 C9 74 0B 8B 01 5E 8B 80 ? ? ? ? FF E0 3B 35 ? ? ? ? 5E 0F 95 C0 C3");
		g_Hooks._localPlayer = std::make_unique<FuncHook>(Localplayer, Hooks::localPlayer);
		uintptr_t tick_entityList = FindSignature("56 8B F1 FF 15 ? ? ? ? 8B 46 50 85 C0 74 11 8B 48 10 8B 70 08 8B 01 FF 50 44 8B C6 85 F6 75 EF 5E C3");
		g_Hooks.entity_tick= std::make_unique<FuncHook>(tick_entityList, Hooks::ActorList_tick);
	}
	LOG_INFO("Hooks initialized");
}

void Hooks::Restore() {
	MH_DisableHook(MH_ALL_HOOKS);
	Sleep(10);
}

void Hooks::Enable() {
	LOG_INFO("Hooks enabled");
	MH_EnableHook(MH_ALL_HOOKS);
}

char Hooks::localPlayer(LocalPlayer* _this) {
	static auto oFunc = g_Hooks._localPlayer->GetFastcall<char, LocalPlayer*>();
	GameData::setCILocalPlayer(_this);
	return  oFunc(_this);
}

void Hooks::ActorList_tick(ActorList* actorList){
	static auto oTick = g_Hooks.entity_tick->GetFastcall<void, ActorList*>();
	GameMode* gm = (GameMode*)Game.getLocalPlayer();
	if (gm != nullptr) moduleMgr->onTick(gm);
	oTick(actorList);
	LOG_INFO("%s -> [%x]",(actorList==(ActorList*)gm)?"LocalPlayer":"Actor",(actorList == (ActorList*)gm) ? (ActorList*)gm : actorList);
	GameData::ActorList_tick(actorList);
}
