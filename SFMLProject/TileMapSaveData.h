#pragma once

struct TileMapSaveData
{
	GameObjectSaveData			gameObjectSaveData;
	std::string					spriteSheetId;
	sf::Vector2u				cellCount;
	sf::Vector2f				cellSize;
	sf::Vector2u				textureTileSize;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(TileMapSaveData, gameObjectSaveData, spriteSheetId, cellCount, cellSize, textureTileSize);
};