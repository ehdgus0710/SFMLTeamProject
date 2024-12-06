#pragma once
#include "Scene.h"

class Yggdrasil;
class Player;
class PauseUIBar;

class Stage2 : public Scene
{
private:
	Player* player;
	Yggdrasil* yggdrasil;

	Rectangle	cameraLimitRect;
	Rectangle	bossClearCameraLimitRect;
	Rectangle	currentCameraLimitRect;
	PauseUIBar* pauseUIBar;

public:
	void CollisitionCheck();
	void LoadResources();

public:
	void Init() override;
	void Enter() override;
	void Exit() override;
	void Release() override;
	void Update(float dt) override;
	void Render(sf::RenderWindow& window)override;

	void Save(const std::string& savePath) override;
	void Load(const std::string& loadPath) override;
public:
	Stage2();
	~Stage2();
};

