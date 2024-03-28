#include "GameData.h"
#include <Windows.h>
#include "../Utils/Logger.h"
#include "../Utils/Utils.h"
#include <set>
#include "Hooks.h"
#include "../SimpleMode/Menu/DrawUtils.h"

GameData Game;
bool GameData::keys[0x256];
bool GameData::isKeyDown(int key) {
	return keys[(int)key];
}
bool GameData::isKeyPressed(int key)
{
	return false;
}
void GameData::terminate()
{
	g_Hooks.actorList.clear();
}
void GameData::initGameData(const SlimUtils::SlimModule* gameModule, SlimUtils::SlimMem* slimMem, void* hDllInst)
{
	{
		HMODULE handler;
		handler = GetModuleHandle("vulkan-1.dll");
		LOG_EVENT("vulkan-1.dll (%p) -> {%s} ", handler, handler ? "OK" : "NO");
		handler = GetModuleHandle("d3d9.dll");
		LOG_EVENT("d3d9.dll (%p) -> {%s} ", handler, handler ? "OK" : "NO");
		handler = GetModuleHandle("d3d10.dll");
		LOG_EVENT("d3d10.dll (%p) -> {%s} ", handler, handler ? "OK" : "NO");
		handler = GetModuleHandle("d3d11.dll");
		if (handler) {impl::D3D11::init();LOG_EVENT("usage functions ->[d3d11.dll{%p}]", handler);}
		LOG_EVENT("d3d11.dll (%p) -> {%s} ", handler, handler ? "OK" : "NO");
		handler = GetModuleHandle("opengl32.dll");
		if (handler) {
		//	impl::Opengl32::init();
			LOG_EVENT("usage->[Opengl32.dll{%p}]", handler);}
		LOG_EVENT("opengl32.dll (%p) -> {%s} ", handler, handler ? "OK" : "NO");
		handler = GetModuleHandle("d3d12.dll");
		LOG_EVENT("d3d12.dll (%p) -> {%s} ", handler, handler ? "OK" : "NO");
	}

}
void GameData::setCILocalPlayer(LocalPlayer* Localplayer) {
	Game.localplayer = Localplayer;
}
LocalPlayer* GameData::getLocalPlayer() {
	if (Game.localplayer == nullptr)
		gameMode = nullptr;
	return Game.localplayer;
}
void GameData::ActorList_tick(ActorList* list) {
	Game.actorList = list;
}
void GameData::forEachEntity(std::function<void(ActorBase*, bool)> callback) {
	if (this->localplayer) {
		for (const auto& ent : g_Hooks.actorList)
			if (ent.ent != nullptr && ent.ent->isplayer == 54) callback(ent.ent, false); //Only get players from this list
		for (const auto& ent : g_Hooks.actorList)
			if (ent.ent != nullptr && ent.ent->isplayer != 54) callback(ent.ent, false); //get everythign else from this
	}
}
void GameData::forEachPlayer(std::function<void(ActorBase*, bool)> callback){
	if (this->localplayer) {
		for (const auto& ent : g_Hooks.actorList)
			if (ent.ent != nullptr && ent.ent->isplayer == 54) callback(ent.ent, false); //Only get players from this list
	}
}
void GameData::forEachMob(std::function<void(ActorBase*, bool)> callback){
	if (this->localplayer) {
		for (const auto& ent : g_Hooks.actorList)
			if (ent.ent != nullptr && ent.ent->isplayer != 54) callback(ent.ent, false); //Only get players from this list
	}
}