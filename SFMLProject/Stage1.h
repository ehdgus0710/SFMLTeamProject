#pragma once
#include "Scene.h"

class PauseUIBar;

class Stage1 : public Scene
{
private:
	Rectangle	cameraLimitRect;
	Rectangle	currentCameraLimitRect;
	PauseUIBar* pauseUIBar;

	SceneIds	changeSceneIds;
	bool		isChangeScene;

public:
	void CollisitionCheck();
	void LoadResources();
	void SetChangeScene(SceneIds id);

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
	Stage1();
	~Stage1();
};

