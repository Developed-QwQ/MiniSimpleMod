#include "Nuker.h"

Nuker::Nuker() :IModule("Nuker", 'N', Category::WORLD, "Break multiple blocks at once.") {

	this->registerIntSetting("Radius", &nukerRadius, nukerRadius, 1, 10);
	this->registerBoolSetting("Autodestroy", &autodestroy, autodestroy);
}

Nuker::~Nuker()
{
}

void Nuker::onTick(GameMode* gm) {
	if (!autodestroy) return;
	Vec3i tempPos = Game.getLocalPlayer()->Pos;
	for (int x = -nukerRadius; x < nukerRadius; x++) {
		for (int y = -nukerRadius; y < nukerRadius; y++) {
			for (int z = -nukerRadius; z < nukerRadius; z++) {
				tempPos.x = (int)Game.getLocalPlayer()->Pos.x + x;
				tempPos.y = (int)Game.getLocalPlayer()->Pos.y + y;
				tempPos.z = (int)Game.getLocalPlayer()->Pos.z + z;
					Game.getLocalPlayer()->destroyBlock(tempPos, 0, false, true);
				
			}
		}
	}
}

std::string Nuker::getModuleName() {
	return "Nuker";
}