#include "GameData.h"
#include <Windows.h>
#include "../Utils/Logger.h"
#include "../Utils/Utils.h"
#include <set>
#include "Hooks.h"

GameData Game;

void GameData::Retrieverenderings()
{
	static bool hasRun = []() {
		Game.rendering = (uintptr_t*)GetFindSignature("d3d11.dll", "8B FF 55 8B EC 6A FF 68 ? ? ? ? 64 A1 ? ? ? ? 50 51 56 A1 ? ? ? ? 33 C5 50 8D 45 F4 64 A3 ? ? ? ? 8B 75 08 81 C6 ? ? ? ? 8B CE E8 ? ? ? ? 8B 55 0C 84 C0 75 51 8B CE E8 ? ? ? ? 84 C0 74 46 8B 86 ? ? ? ? 03 86 ? ? ? ? 3B D0 72 1A 8D 86 ? ? ? ? C7 45 F0 ? ? ? ? 50 8D 4D F0 E8 ? ? ? ? 84 C0 74 1C 6A 00 51 8B CE E8 62 B0 0D 00");
		LOG_INFO("rendering: %p->{%s}", Game.rendering, Game.rendering ? "OK" : "NO");
		return true;
	}();
}

void GameData::initGameData()
{
	{
		HMODULE handler;
		handler = GetModuleHandle("opengl32.dll");
		LOG_INFO("opengl32.dll (%p) -> {%s} ", handler, handler ? "OK" : "NO");
		handler = GetModuleHandle("vulkan-1.dll");
		LOG_INFO("vulkan-1.dll (%p) -> {%s} ", handler, handler ? "OK" : "NO");
		handler = GetModuleHandle("d3d9.dll");
		LOG_INFO("d3d9.dll (%p) -> {%s} ", handler, handler ? "OK" : "NO");
		handler = GetModuleHandle("d3d10.dll");
		LOG_INFO("d3d10.dll (%p) -> {%s} ", handler, handler ? "OK" : "NO");
		handler = GetModuleHandle("d3d11.dll");
		LOG_INFO("d3d11.dll (%p) -> {%s} ", handler, handler ? "OK" : "NO");
		handler = GetModuleHandle("d3d12.dll");
		LOG_INFO("d3d12.dll (%p) -> {%s} ", handler, handler ? "OK" : "NO");
		handler = GetModuleHandle("libSandboxEngine.dll");
		LOG_INFO("libSandboxEngine.dll (%p) -> {%s} ", handler, handler ? "OK" : "NO");
	}
	//Retrieverenderings();
}

void GameData::setCILocalPlayer(LocalPlayer* Localplayer) {
	//	LOG_INFO("setCILocalPlayer->(%p)", Localplayer);
	Game.localplayer = Localplayer;
}

LocalPlayer* GameData::getLocalPlayer() {
	if (Game.localplayer == nullptr)
		gameMode = nullptr;
	return Game.localplayer;
}

void GameData::ActorList_tick(ActorList* list){
	Game.actorList = list;
}

void GameData::forEachEntity(std::function<void(ActorList*, bool)> callback)
{
	//if (this->localplayer) {
	//	for (const auto& ent : g_Hooks.actorList) if (ent.ent != nullptr && ent.ent->isPlayer()) callback(ent.ent, false); //Only get players from this list
	//	for (const auto& ent : Game.getLocalPlayer()->level->getMiscEntityList())
	//		if (ent != nullptr && ent->getEntityTypeId() >= 1 && ent->getEntityTypeId() <= 999999999 && !ent->isPlayer()) callback(ent, false); //get everythign else from this
	//}
}

void GameData::forEachPlayer(std::function<void(ActorList*, bool)>)
{
}

void GameData::forEachMob(std::function<void(ActorList*, bool)>)
{
}
