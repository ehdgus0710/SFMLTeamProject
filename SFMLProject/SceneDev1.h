#pragma once
#include "Scene.h"

class Player;
class Yggdrasil;
class WallCollisionObject;
class BackgroundColorBox;

class SceneDev1 : public Scene
{
private:
	WallCollisionObject*	cameraWallCollisionObject;
	Player*					player;
	Yggdrasil*				yggdrasil;
	Rectangle				cameraLimitRect;
	Rectangle				currentCameraLimitRect;
	BackgroundColorBox*		backgroundColorBox;
	
public:
	void CollisitionCheck();
	void LoadResources();
public:
	void Init() override;
	void Enter() override;
	void Exit() override;
	void Release() override;
	void Update(float deltaTime) override;
	void Render(sf::RenderWindow& window)override;

	void Save(const std::string& savePath) override;
	void Load(const std::string& loadPath) override;
public:
	SceneDev1();
	~SceneDev1();

};

