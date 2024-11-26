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


struct GameClearSaveData
{
	GameObjectSaveData	gameObjectSaveData;
	sf::Vector2f maxStartPosition;
	sf::Vector2f destinationPosition;
	sf::Vector2f endMovePosition;

	float endMoveTime;
	float moveTime;


	NLOHMANN_DEFINE_TYPE_INTRUSIVE(GameClearSaveData, gameObjectSaveData, maxStartPosition, destinationPosition, endMovePosition, endMoveTime, moveTime);
};

struct EnemySpawnerSaveData
{
	GameObjectSaveData	gameObjectSaveData;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(EnemySpawnerSaveData, gameObjectSaveData);
};