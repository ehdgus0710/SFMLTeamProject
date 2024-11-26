#pragma once

#include "GameObjectSaveData.h"

struct WallCollisionSaveData
{
	GameObjectSaveData			gameObjectSaveData;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(WallCollisionSaveData, gameObjectSaveData);
};

