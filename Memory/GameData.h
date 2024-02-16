#pragma once
#include <iostream>
#include <functional>
#include <map>
#include <mutex>
#include <queue>
#include <unordered_set>
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
	static void Retrieverenderings();
public:
	static void initGameData();
	static void setCILocalPlayer(LocalPlayer* Localplayer);
	LocalPlayer* getLocalPlayer();
	static void ActorList_tick(ActorList* list);

	GameMode* getGameMode() { return gameMode; };
	void forEachEntity(std::function<void(ActorList*, bool)>);
	void forEachPlayer(std::function<void(ActorList*, bool)>);
	void forEachMob(std::function<void(ActorList*, bool)>);
};
extern GameData Game;
