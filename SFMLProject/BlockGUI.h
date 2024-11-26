#pragma once

#include "ComponentGUI.h"
#include "imgui.h"

class BlockObject;
class ItemBlockObject;

class BlockGUI : public ComponentGUI
{
protected:
	BlockObject*		blockObject;
	ItemBlockObject*	itemBlockObject;
	sf::Texture*		texture;
	ImVec2				tileUvSize;

	bool				isChangeRectItemBlock;
	bool				isChangeRect;	
	int					heightCount;
	int					widthCount;

public:
	void Update() override;
	void SetObject(GameObject* object) override;

public:
	BlockGUI();
	~BlockGUI();
};

