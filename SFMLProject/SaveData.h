#pragma once

namespace sf
{
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(sf::Vector2f, x, y);
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(sf::Vector2u, x, y);
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(sf::IntRect, left, top, width, height);
}

#include "GameObjectSaveData.h"
#include "PlayerSaveData.h"
#include "BlockSaveData.h"
#include "WallCollisionSaveData.h"
#include "TileMapSaveData.h"
#include "EnemySaveData.h"

struct SaveData
{
public:
	int version = 0;
	PlayerSaveData						playerData;
	std::vector<BlockSaveData>			blockSaveDatas;
	std::vector<ItemBlockSaveData>		itemBlockSaveDatas;
	std::vector<WallCollisionSaveData>	wallCollisionSaveDatas;
	TileMapSaveData						tileMapSaveData;

	virtual SaveData* VersionUp() = 0;
};

struct SaveDataV1 : public SaveData
{

public:
	SaveData* VersionUp() override;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(SaveDataV1, version, playerData, blockSaveDatas, itemBlockSaveDatas, wallCollisionSaveDatas, tileMapSaveData);

public:
	SaveDataV1() { version = 1; }
};

struct SaveDataV2 : public SaveData
{
public:
	std::vector<SavePointSaveData>		savePointSaveDatas;
	std::vector<GameClearSaveData>		gameClearSaveDatas;
	std::vector<EnemySaveData>			enemySaveDatas;
	std::vector<EnemySpawnerSaveData>	enemySpawnerSaveDatas;

	int highscore;
public:
	SaveData* VersionUp() override;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(SaveDataV2, version, playerData, blockSaveDatas, itemBlockSaveDatas
		, wallCollisionSaveDatas, tileMapSaveData, savePointSaveDatas, gameClearSaveDatas, enemySaveDatas, enemySpawnerSaveDatas, highscore);
public:
	SaveDataV2() : 
		highscore(0)
	{ version = 2; }
	SaveDataV2(const SaveDataV1& other) :
		highscore(0)
	{
		version = 2;
		playerData = std::move(other.playerData);
		blockSaveDatas = std::move(other.blockSaveDatas);
		itemBlockSaveDatas = std::move(other.itemBlockSaveDatas);
		wallCollisionSaveDatas = std::move(other.wallCollisionSaveDatas);
		tileMapSaveData = std::move(other.tileMapSaveData);
	}
};


typedef SaveDataV2 SaveDataVC;
