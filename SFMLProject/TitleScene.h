#pragma once
#include "Scene.h"

class FadeOutUI;
class TitleScene : public Scene
{
private:
	FadeOutUI* fadeOutUI;

	bool isStartGame;
	bool isEndGame;

public:
	void CollisitionCheck();
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
	void StartGame();
	void EndGame();
public:
	TitleScene();
	~TitleScene();
};