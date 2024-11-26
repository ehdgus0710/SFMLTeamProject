#pragma once

enum class ComponentGUIType
{
	Animator,
	Collider,
	TileMap,
	TileMapController,
	SavePoint,
	EnemySpawner,
	End
};

class ComponentGUI
{
protected:
	GameObject*			target;
	ComponentGUIType	type;

public:
	virtual void Update() = 0;
	virtual void SetObject(GameObject* object) = 0;

public:
	ComponentGUI(ComponentGUIType type);
	~ComponentGUI();
};

