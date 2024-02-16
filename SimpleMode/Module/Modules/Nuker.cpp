#include "Nuker.h"

Nuker::Nuker() :IModule("Nuker", 'N', Category::WORLD, "Break multiple blocks at once.") {
	this->registerIntSetting("Radius", &nukerRadius, nukerRadius, 1, 10);
	this->registerBoolSetting("Autodestroy", &autodestroy, autodestroy);
}

Nuker::~Nuker()
{
}

void Nuker::onTick(GameMode* gm){
	if (!autodestroy) return;
	Vec3i tempPos = gm->player->Pos;
	for (int x = -nukerRadius; x < nukerRadius; x++) {
		for (int y = -nukerRadius; y < nukerRadius; y++) {
			for (int z = -nukerRadius; z < nukerRadius; z++) {
				tempPos.x = (int)gm->player->Pos.x + x;
				tempPos.y = (int)gm->player->Pos.y + y;
				tempPos.z = (int)gm->player->Pos.z + z;
				if (tempPos.y > 0) {
					Game.getLocalPlayer()->destroyBlock(tempPos,64,true,true);
				}
			}
		}
	}
}

const char* Nuker::getModuleName(){
	return "Nuker";
}