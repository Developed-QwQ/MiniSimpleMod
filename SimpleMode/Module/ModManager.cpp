#include "ModManager.h"

ModManager::ModManager(GameData* gameData) {
	gameData = gameData;
}

ModManager::~ModManager() {
	initialized = false;
	auto lock = lockModuleListExclusive();
	moduleList.clear();
}

void ModManager::initMods() {
	LOG_INFO("Initializing modules.");
	{
		auto lock = lockModuleListExclusive();
		this->moduleList.push_back(std::shared_ptr<IModule>(new ModuleList));
		this->moduleList.push_back(std::shared_ptr<IModule>(new Rangeblock));
		this->moduleList.push_back(std::shared_ptr<IModule>(new Killaura));
		this->moduleList.push_back(std::shared_ptr<IModule>(new Airjump));
		this->moduleList.push_back(std::shared_ptr<IModule>(new D3DEsp));
		this->moduleList.push_back(std::shared_ptr<IModule>(new AutoTP));
		this->moduleList.push_back(std::shared_ptr<IModule>(new Nuker));
		this->moduleList.push_back(std::shared_ptr<IModule>(new speed));
		this->moduleList.push_back(std::shared_ptr<IModule>(new Bhop));
		this->moduleList.push_back(std::shared_ptr<IModule>(new Derp));
		this->moduleList.push_back(std::shared_ptr<IModule>(new Fly));

		std::sort(moduleList.begin(), moduleList.end(), [](auto lhs, auto rhs) {
			auto current = lhs;
			auto other = rhs;
			return std::string{*current->getModuleName().c_str()} < std::string{*other->getModuleName().c_str()};
			});

		initialized = true;
	}
}

void ModManager::deInitMods() {
	for (auto& mod : this->moduleList)
		mod.get()->setEnabled(false);
	this->moduleList.clear();
}

void ModManager::onTick(GameMode* gameMode) {
	if (!isInitialized())
		return;
	auto lock = lockModuleList();
	for (auto& mod : moduleList) {
		if (mod->isEnabled())
			mod->onTick(gameMode);
	}
}

void ModManager::onKeyUpdate(int key, bool isDown)
{
	if (!isInitialized())
		return;
	auto lock = lockModuleList();
	for (auto& mod : moduleList) {
		mod->onKeyUpdate(key, isDown);
	}
}

void ModManager::onKey(int key, bool isDown, bool& shouldCancel)
{
	if (!isInitialized())
		return;
	auto mutex = lockModuleList();

	for (auto& mod : moduleList) {
		if (mod->isEnabled())
			mod->onKey(key, isDown, shouldCancel);
	}
}

void ModManager::onAttack(ActorBase* attackedEnt)
{
	if (!isInitialized())
		return;

	auto lock = lockModuleList();
	for (auto& mod : moduleList) {
		if (mod->isEnabled())
			mod->onAttack(attackedEnt);
	}
}

void ModManager::onPlayerTick(Player* player)
{
	if (!isInitialized())
		return;
	auto lock = lockModuleList();
	for (auto& it : moduleList) {
		if (it->isEnabled())
			it->onPlayerTick(player);
	}
}

void ModManager::onLoadConfig(void* conf)
{
}

void ModManager::onSaveConfig(void* conf)
{
}

void ModManager::toggle()
{
}

std::vector<std::shared_ptr<IModule>>* ModManager::getModuleList() {
	return &moduleList;
}

ModManager* moduleMgr = new ModManager(&Game);