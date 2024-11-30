#pragma once
#include "Scene.h"
class Stage1 :
    public Scene
{
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
	Stage1();
	~Stage1();
};

