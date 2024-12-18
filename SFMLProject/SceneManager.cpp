#include "stdafx.h"
#include "SceneManager.h"

#include "SceneDev1.h"
#include "SceneDev2.h"
#include "TitleScene.h"

#include "Stage1.h"
#include "Stage2.h"

void SceneManager::Init()
{
	sceneVec.push_back(new SceneDev1());
	sceneVec.push_back(new SceneDev2());
	sceneVec.push_back(new TitleScene());
	sceneVec.push_back(new SceneDev2());
	sceneVec.push_back(new Stage2());

	for (auto& scene : sceneVec)
	{
		scene->Init();
	}

	currentScene = startScene;
	currentScene = SceneIds::SceneDev1;
	sceneVec[(int)currentScene]->Enter();
}

void SceneManager::Release()
{
	for (auto& scene : sceneVec)
	{
		scene->Release();
		delete scene;
	}

	sceneVec.clear();
}

void SceneManager::ChangeScene(SceneIds id)
{
	sceneVec[(int)currentScene]->Exit();
	currentScene = id;
	sceneVec[(int)currentScene]->Enter();
}

void SceneManager::Update(float deltaTime)
{
	sceneVec[(int)currentScene]->Update(deltaTime);
}

void SceneManager::FixedUpdate(float fixedDeltaTime)
{
	sceneVec[(int)currentScene]->FixedUpdate(fixedDeltaTime);
}

void SceneManager::Render(sf::RenderWindow& window)
{
	sceneVec[(int)currentScene]->Render(window);
}
