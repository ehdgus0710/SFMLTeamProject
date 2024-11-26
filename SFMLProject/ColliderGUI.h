#pragma once

#include "ComponentGUI.h"

class ColliderGUI : public ComponentGUI
{
protected:
	Collider* collider;

public:
	void Update() override;
	void SetObject(GameObject* object) override;

public:
	ColliderGUI();
	~ColliderGUI();
};