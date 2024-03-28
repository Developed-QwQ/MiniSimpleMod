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
	LOG_EVENT("Setting up Hooks...");
	{
		uintptr_t _Localplayer = utils->FindSignatureModule("libSandboxEngine.dll", "56 8B F1 83 BE ? ? ? ? ? 74 2A E8 ? ? ? ? 85 C0 74 21 8B 86 ? ? ? ? 85 C0 7E 07 48 89 86 ? ? ? ? 8B 06 8B CE 6A 00 6A 00 6A 00 FF 90 ? ? ? ? 5E");
		g_Hooks.localPlayeres = std::make_unique<FuncHook>(_Localplayer, Hooks::localPlayers);
		uintptr_t tick_entityList = utils->FindSignatureModule("libSandboxEngine.dll", "56 8B F1 FF 15 ? ? ? ? 8B 46 50 85 C0 74 11 8B 48 10 8B 70 08 8B 01 FF 50 44 8B C6 85 F6 75 EF 5E C3");
		g_Hooks.entity_tick = std::make_unique<FuncHook>(tick_entityList, Hooks::ActorList_tick);
		uintptr_t ontick_playerTick = utils->FindSignatureModule("libSandboxEngine.dll", "55 8B EC 83 EC 08 53 56 57 8B F9 E8 ? ? ? ? 8B F0 89 75 F8 8B 9E 60 02 00 00 85 DB 0F 84 ? ? ? ? 8B 13 8B CB 8B 52 58 FF D2 84 C0 0F 84");
		g_Hooks.Actor_playerTick= std::make_unique<FuncHook>(ontick_playerTick, Hooks::Actor_PlayerTick);
		uintptr_t setBlock = utils->FindSignatureModule("libSandboxEngine.dll","55 8B EC 51 53 56 8B 75 0C 57 8B F9 8B 4D 18 C1 E1 1C 0B 4D 14 8B D9 8B C1 C1 FB 10 33 D9 C1 F8 10 81 E3 ? ? ? ? C1 F9 0C 33 D8 80 E1 7F");
		//g_Hooks.setblock= std::make_unique<FuncHook>(setBlock, Hooks::setBlockAll);
		uintptr_t MessageboxText = utils->FindSignatureModule("libiworld.dll","55 8B EC 83 EC 08 56 8B F1 E8 ? ? ? ? 83 7E 14 00 8B 55 08 89");
		g_Hooks.text= std::make_unique<FuncHook>(MessageboxText, Hooks::TextMessage);

		{  //vtable Hook
			if (Game.getLocalPlayer() != nullptr) {
				uintptr_t Localplayer = *(uintptr_t*)Game.getLocalPlayer();
				if (Localplayer == NULL) {
					LOG_ERROR("LoopbackPacketSenderVtable is invalid");
				}
				else {

				}
			
			}
		}
		{//Module_Name Hook
		 
		
		}
	}
	LOG_EVENT("Hooks initialized");
}

void Hooks::Restore() {
	MH_DisableHook(MH_ALL_HOOKS);
	Sleep(10);
}

void Hooks::Enable() {
	LOG_EVENT("Hooks enabled");
	MH_EnableHook(MH_ALL_HOOKS);
}

char* _fastcall Hooks::TextMessage(__int32 MessageID){
	static auto oFunc = g_Hooks.text->GetFastcall<char*, __int32>();
	return oFunc(MessageID);
}

void Hooks::localPlayers(LocalPlayer* _this) {
	static auto oFunc = g_Hooks.localPlayeres->GetFastcall<void, LocalPlayer*>();
	oFunc(_this);
	GameData::setCILocalPlayer(_this);
}

void Hooks::ActorList_tick(ActorList* actorList) {
	static auto oTick = g_Hooks.entity_tick->GetFastcall<void, ActorList*>();
	GameMode* gm = (GameMode*)Game.getLocalPlayer();
	if (actorList != nullptr) moduleMgr->onAttack((ActorBase*)actorList);
	if (gm != nullptr) moduleMgr->onTick(gm);
	oTick(actorList);
	GameData::ActorList_tick(actorList);
}

int Hooks::setBlockAll(void* _this, int a2, int a3, Vec3i pos){
	static auto oFunc = g_Hooks.setblock->GetFastcall<int, void*,int,int,Vec3i>();
	LOG_INFO("pos x[%d] y[%d] z[%d]",pos.x, pos.y, pos.z);
	return oFunc(_this, a2, a3,pos);
}	

Player  Hooks::Actor_PlayerTick(Player* _this){
	static auto oTick = g_Hooks.Actor_playerTick->GetFastcall<Player, Player*>();
	if (_this != nullptr)moduleMgr->onPlayerTick(_this);
	return oTick(_this);
}
