#pragma once

#include "ComponentGUI.h"
class GameClearObject;

class GameClearPointGUI : public ComponentGUI
{
protected:
	GameClearObject* clearObject;

public:
	void Update() override;
	void SetObject(GameObject* object) override;

public:
	GameClearPointGUI();
	~GameClearPointGUI();
};