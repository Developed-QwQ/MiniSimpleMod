#include "AutoTP.h"

AutoTP::AutoTP() :IModule("AutoTP", 0, Category::PLAYER, u8"让你可以传送到实体的上方！") {
	this->registerIntSetting("radius", &this->radius, this->radius, 0, 15);
}

AutoTP::~AutoTP()
{
}

std::string AutoTP::getModuleName() {
	return "AutoTP";
}
void AutoTP::onAttack(ActorBase* actorbase) {
	if (actorbase == nullptr) return;
	if (actorbase->isplayer == 17 ) return;
	if (actorbase->isDead()) return;
	if (actorbase == Game.getLocalPlayer()) return;
	PlayerLocoMotion* actorbaseLocoMotion = actorbase->playerlocomotion;
	PlayerLocoMotion* LocalplayerLocoMotion = Game.getLocalPlayer()->playerlocomotion;
	int dist = (pos(actorbaseLocoMotion->xyzPos)).dist(pos(LocalplayerLocoMotion->xyzPos));Odelay++;
	if (Odelay > 20 && dist < radius) {
		if (this->isEnabled()) {
			actorbaseLocoMotion->xyzPos.y+=2;
			LocalplayerLocoMotion->xyzPos = actorbaseLocoMotion->xyzPos;
		}Odelay = 0;
	}
}