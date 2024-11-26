#pragma once

#include "GameObjectSaveData.h"
#include "Defines.h"

struct PlayerSaveData
{
	GameObjectSaveData			gameObjectSaveData;
	DefaultStatus				status;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(PlayerSaveData, gameObjectSaveData, status);
};
