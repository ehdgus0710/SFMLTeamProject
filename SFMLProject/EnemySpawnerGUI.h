#pragma once

#include "ComponentGUI.h"
class EnemySpawner;

class EnemySpawnerGUI : public ComponentGUI
{
public:

    struct EnemySpawnerTypeEnum
    {
        EnemyType type;
        std::string name;
    };

protected:
	EnemySpawner*	enemySpawner;
	EnemyType		currentType;
public:
	void Update() override;
	void SetObject(GameObject* object) override;

public:
	EnemySpawnerGUI();
	~EnemySpawnerGUI();
};