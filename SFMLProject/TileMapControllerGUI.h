#pragma once

#include "ComponentGUI.h"
#include "imgui.h"

class TileMapController;

class TileMapControllerGUI : public ComponentGUI
{
private:
	sf::Texture*				texture;
	std::vector<std::string>    textureVector;
	TileMapController*			tileMapController;
	std::string					saveName;

	sf::Vector2u				cellCount;
	sf::Vector2f				cellSize;
	sf::Vector2u				tileTextureSize;

	ImVec2						tileUvSize;

	int							heightCount;
	int							widthCount;
	int							selectTileX;
	int							selectTileY;

	bool						isSelect;
public:
	void Update() override;
	void SetObject(GameObject* object) override;

public:
	TileMapControllerGUI();
	~TileMapControllerGUI();
};

