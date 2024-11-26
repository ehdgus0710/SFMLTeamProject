#pragma once


#include "TileMapSaveData.h"

class TileMap;

class TileMapController : public GameObject
{
protected:
	std::vector<TileMap*>	tileMaps;
	std::string				spriteSheetId;
	sf::Vector2u			cellCount;
	sf::Vector2f			cellSize;
	sf::Vector2u			textureTileSize;
public:

	void SetSpriteSheetId(const std::string& spriteID) { spriteSheetId = spriteID; }
	const std::string& GetSpriteSheetId() { return spriteSheetId; }

	void SetCellCount(const sf::Vector2u& tileCount);
	const sf::Vector2u& GetTileCount() { return cellCount; }

	void SetCellSize(const sf::Vector2f& cellSize);
	const sf::Vector2f& GetCellSize() const { return cellSize; }

	void SetTileTextrueRectSize(const sf::Vector2u& texTileSize);
	const sf::Vector2u& GetTileTextureRectSize() const { return textureTileSize; }

public:
	void AddTileMap(int count);

	bool SaveCsv(const std::string& filePath) const override;
	bool LoadCsv(const std::string& filePath) override;

	TileMapSaveData GetTileMapSaveData() const;
	void LoadTileMapSaveData(const TileMapSaveData& data);

	sf::FloatRect GetLocalBounds() const override;
	sf::FloatRect GetGlobalBounds() const override;
public:
	TileMapController(const std::string& name);
	virtual ~TileMapController();
};

