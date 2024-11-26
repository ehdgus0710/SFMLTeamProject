#pragma once

#include "SaveData.h"

struct GameObjectSaveData
{
	std::string			name;
	sf::Vector2f		position;
	float				rotation;
	sf::Vector2f		scale;
	sf::Vector2f		origin;
	int					originPreset;
	bool				active;
	int					sortingOrder;
	int					layerType;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(GameObjectSaveData, name, position, rotation, scale, origin, originPreset, active, sortingOrder, layerType);
};


struct SavePointSaveData
{
	GameObjectSaveData	gameObjectSaveData;
	sf::Vector2f	restartPosition;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(SavePointSaveData, gameObjectSaveData, restartPosition);
};

struct EnemySpawnerSaveData
{
	GameObjectSaveData	gameObjectSaveData;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(EnemySpawnerSaveData, gameObjectSaveData);
};