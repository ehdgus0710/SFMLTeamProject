#pragma once

namespace sf
{
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(sf::Vector2f, x, y);
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(sf::Vector2u, x, y);
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(sf::IntRect, left, top, width, height);
}

#include "GameObjectSaveData.h"
#include "PlayerSaveData.h"
#include "WallCollisionSaveData.h"
#include "TileMapSaveData.h"
#include "EnemySaveData.h"

struct SaveData
{
public:
	int version = 0;
	PlayerSaveData						playerData;
	std::vector<WallCollisionSaveData>	wallCollisionSaveDatas;
	TileMapSaveData						tileMapSaveData;

	virtual SaveData* VersionUp() = 0;
};

struct SaveDataV1 : public SaveData
{

public:
	SaveData* VersionUp() override;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(SaveDataV1, version, playerData, wallCollisionSaveDatas, tileMapSaveData);

public:
	SaveDataV1() { version = 1; }
};

struct SaveDataV2 : public SaveData
{
public:
	std::vector<SavePointSaveData>		savePointSaveDatas;
	std::vector<EnemySaveData>			enemySaveDatas;
	std::vector<EnemySpawnerSaveData>	enemySpawnerSaveDatas;

public:
	SaveData* VersionUp() override;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(SaveDataV2, version, playerData,  wallCollisionSaveDatas, tileMapSaveData, savePointSaveDatas, enemySaveDatas, enemySpawnerSaveDatas);
public:
	SaveDataV2()
	{ version = 2; }
	SaveDataV2(const SaveDataV1& other) 
	{
		version = 2;
		playerData = std::move(other.playerData);
		wallCollisionSaveDatas = std::move(other.wallCollisionSaveDatas);
		tileMapSaveData = std::move(other.tileMapSaveData);
	}
};


typedef SaveDataV2 SaveDataVC;
