#pragma once
#include <iostream>
#include <functional>
#include <map>
#include <mutex>
#include <queue>
#include <unordered_set>

#include <string.h>
#include <time.h>
#include <D3D11.h>
#include <tchar.h>
#include <DXGI.h>
#include "SlimMem.h"
#include "../Utils/logger.h"
#include "../SDK/GameMode.h"
#include "../SDK/ActorList.h"
class GameData {
private:
	uintptr_t* rendering = nullptr;
	LocalPlayer* localplayer = nullptr;
	GameMode* gameMode = nullptr;
	ActorList* actorList = nullptr;
private:
	const SlimUtils::SlimModule* gameModule = 0;
public:
	//static SlimUtils::SlimMem* slimMem;
	static bool keys[0x256];

	static bool isKeyDown(int key);
	static bool isKeyPressed(int key);
	static void terminate();

	static void initGameData(const SlimUtils::SlimModule* gameModule, SlimUtils::SlimMem* slimMem, void* hDllInst);
	static void setCILocalPlayer(LocalPlayer* Localplayer);
	LocalPlayer* getLocalPlayer();
	static void ActorList_tick(ActorList* list);

	GameMode* getGameMode() { return gameMode; };
	void forEachEntity(std::function<void(ActorBase*, bool)>);
	void forEachPlayer(std::function<void(ActorBase*, bool)>);
	void forEachMob(std::function<void(ActorBase*, bool)>);
};
extern GameData Game;
