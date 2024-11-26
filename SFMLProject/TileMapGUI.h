#pragma once

#include "ComponentGUI.h"
#include "imgui.h"

class TileMap;

class TileMapGUI : public ComponentGUI
{
private:
	sf::Vector2f	cellSize;
	sf::Vector2u	tileTextureSize;

	ImVec2			tileUvSize;

	sf::Vector2f	textureSize;
	int				heightCount;
	int				widthCount;

	int				selectTileX;
	int				selectTileY;

	bool			isSelect;

protected:
	TileMap* tileMap;
	sf::Texture* texture;

	bool isTileMapEditor;
public:
	void Update() override;
	void SetObject(GameObject* object) override;
	void OnTileMapEditor();
public:
	TileMapGUI();
	~TileMapGUI();
};

