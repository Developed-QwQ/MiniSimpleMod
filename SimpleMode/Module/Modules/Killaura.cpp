#include "Killaura.h"

Killaura::Killaura() :IModule("Killaura", 'R', Category::COMBAT, "Attacks entities around you automatically.") {
	this->registerIntSetting("Range", &range, range, 0, 20);
	this->registerIntSetting("Delay", &delay, delay, 1, 20);

}

Killaura::~Killaura()
{
}

std::string Killaura::getModuleName()
{
	return "Killaura";
}
bool mouse = false;
static std::vector<ActorBase*> targetList;
void Killaura::onAttack(ActorBase* actorbase){
	if (actorbase == nullptr)return;
	if (actorbase->isplayer == 17) return;  //Item
	if (actorbase->isDead()) return;
	if (actorbase == Game.getLocalPlayer()) return;
	PlayerLocoMotion* playerLocoMotion = actorbase->playerlocomotion;
	PlayerLocoMotion* LocalplayerLocoMotion = Game.getLocalPlayer()->playerlocomotion;
	int dist = (pos(playerLocoMotion->xyzPos)).dist(pos(LocalplayerLocoMotion->xyzPos));
	mouse = !mouse;Odelay++;
	if (Odelay > delay && dist< range) {
		if (this->isEnabled()) {
			Game.getLocalPlayer()->interactActor(actorbase, 0, mouse);
		}Odelay = 0;
	}
}
