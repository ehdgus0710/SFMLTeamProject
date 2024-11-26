#pragma once
struct EnemySaveData
{
	GameObjectSaveData			gameObjectSaveData;
	int							enemyType;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(EnemySaveData, gameObjectSaveData, enemyType);
};