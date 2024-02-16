#include "Killaura.h"

Killaura::Killaura() :IModule("Killaura",'R',Category::COMBAT,"Attacks entities around you automatically."){

	this->registerFloatSetting("Range", &range, range, 2.f, 20.f);
}

Killaura::~Killaura()
{
}

const char* Killaura::getModuleName()
{
    return "Killaura";
}	
static std::vector<ActorList*> targetList;
void findEntity(ActorList* currentEntity, bool isRegularEntity) {
	//static auto killauraMod = moduleMgr->getModule<Killaura>();
	if (currentEntity == nullptr)
		return;
	if (currentEntity == (ActorList*)Game.getLocalPlayer())  // Skip Local player
		return;
	if (!Game.getLocalPlayer()->canAttack())
		return;
	if (Game.getLocalPlayer()->canAttack())
		return;
	Game.getLocalPlayer()->doActualAttack(currentEntity,true);
}

void Killaura::onTick(GameMode* gm)
{
	Game.forEachEntity(findEntity);
}

void Killaura::onEnable()
{
}
