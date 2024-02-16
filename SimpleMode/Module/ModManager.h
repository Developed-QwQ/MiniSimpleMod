#pragma once
#include "../../Utils/logger.h"
#include "Modules/IModule.h"

#include <typeinfo>
#include <vector>
#include <optional>
#include <memory>
#include <mutex>
#include <shared_mutex>

#include "../../Memory/GameData.h"
class ModManager {
private:
	GameData* gameData;
	bool initialized = false;
	std::shared_mutex moduleListMutex;
public:
	std::vector<std::shared_ptr<IModule>> moduleList;
	ModManager(GameData* gameData);
	~ModManager();
	//std::vector<std::shared_ptr<IModule>> COMBAT;
	void initMods();
	void deInitMods();
	virtual void onTick(GameMode* gameMode);
	virtual void onKeyUpdate(int key, bool isDown);
	virtual void onKey(int key, bool isDown, bool& shouldCancel);
	virtual void onAttack(ActorBase* attackedEnt);
	virtual void onPlayerTick(Player* player);
	virtual void onLoadConfig(void* conf);
	virtual void onSaveConfig(void* conf);
	virtual void toggle();

	std::shared_lock<std::shared_mutex> lockModuleList() { return std::shared_lock(moduleListMutex); }
	std::unique_lock<std::shared_mutex> lockModuleListExclusive() { return std::unique_lock(moduleListMutex); }

	std::shared_mutex* getModuleListLock() { return &moduleListMutex; }

	bool isInitialized() { return initialized; };
	std::vector<std::shared_ptr<IModule>>* getModuleList();

	template <typename TRet>
	TRet* getModule() {
		if (!isInitialized())
			return nullptr;
		auto lock = lockModuleList();
		for (auto pMod : moduleList) {
			if (auto pRet = dynamic_cast<typename std::remove_pointer<TRet>::type*>(pMod.get())) {

				return pRet;
			}
		}
		return nullptr;
	};
};
extern ModManager* moduleMgr;
