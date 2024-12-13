#include "stdafx.h"
#include "ControllerUIBar.h"

#include "Scene.h"
#include "KeyActionUI.h"

ControllerUIBar::ControllerUIBar(const std::string& texId, const std::string& name)
	: UISpriteGameObject(texId, name)
{
	CreateActionKeyUI();
}

void ControllerUIBar::CreateActionKeyUI()
{
	Scene* currentScene = SceneManager::GetInstance().GetCurrentScene();
	
	sf::Vector2f createPosition = { 920.f, 200.f };
	for (int i = 0; i < (int)ActionKeyType::end; ++i)
	{
		switch ((ActionKeyType)i)
		{
		case ActionKeyType::LeftMove:
			keyActionUIVector.push_back(currentScene->AddGameObject(new KeyActionUI("LeftMove", ActionKeyType::LeftMove, "Status", "LeftMoveUI", 30, { 98 , 73, 59, 255 }, { 174,151,133,255 }), LayerType::UI));
			break;
		case ActionKeyType::RightMove:
			keyActionUIVector.push_back(currentScene->AddGameObject(new KeyActionUI("RightMove", ActionKeyType::RightMove, "Status", "RightMoveUI", 30, { 98 , 73, 59, 255 }, { 174,151,133,255 }), LayerType::UI));
			break;
		case ActionKeyType::Dash:
			keyActionUIVector.push_back(currentScene->AddGameObject(new KeyActionUI("Dash", ActionKeyType::Dash, "Status", "DashUI", 30, { 98 , 73, 59, 255 }, { 174,151,133,255 }), LayerType::UI));
			break;
		case ActionKeyType::Attack:
			keyActionUIVector.push_back(currentScene->AddGameObject(new KeyActionUI("Attack", ActionKeyType::Attack, "Status", "AttackUI", 30, { 98 , 73, 59, 255 }, { 174,151,133,255 }), LayerType::UI));
			break;
		case ActionKeyType::Skill1:
			keyActionUIVector.push_back(currentScene->AddGameObject(new KeyActionUI("Skill1", ActionKeyType::Skill1, "Status", "Skill1UI", 30, { 98 , 73, 59, 255 }, { 174,151,133,255 }), LayerType::UI));
			break;
		case ActionKeyType::Skill2:
			keyActionUIVector.push_back(currentScene->AddGameObject(new KeyActionUI("Skill2", ActionKeyType::Skill2, "Status", "Skill2UI", 30, { 98 , 73, 59, 255 }, { 174,151,133,255 }), LayerType::UI));
			break;
		case ActionKeyType::Jump:
			keyActionUIVector.push_back(currentScene->AddGameObject(new KeyActionUI("Jump", ActionKeyType::Jump, "Status", "JumpUI", 30, { 98 , 73, 59, 255 }, { 174,151,133,255 }), LayerType::UI));
			break;
		case ActionKeyType::ChangeSkul:
			keyActionUIVector.push_back(currentScene->AddGameObject(new KeyActionUI("ChangeSkul", ActionKeyType::ChangeSkul, "Status", "ChangeSkulUI", 30, { 98 , 73, 59, 255 }, { 174,151,133,255 }), LayerType::UI));
			break;
		case ActionKeyType::Item:
			keyActionUIVector.push_back(currentScene->AddGameObject(new KeyActionUI("Item", ActionKeyType::Item, "Status", "ItemUI", 30, { 98 , 73, 59, 255 }, { 174,151,133,255 }), LayerType::UI));
			break;
		case ActionKeyType::Down:
			keyActionUIVector.push_back(currentScene->AddGameObject(new KeyActionUI("Down", ActionKeyType::Down, "Status", "DownUI", 30, { 98 , 73, 59, 255 }, { 174,151,133,255 }), LayerType::UI));
			break;
		case ActionKeyType::end:
			break;
		default:
			break;
		}

		keyActionUIVector[i]->sortingOrder = 5;
		keyActionUIVector[i]->SetScale({ 3.f,3.f });
		keyActionUIVector[i]->SetPosition({ createPosition.x + (i / 2 == 0 ? -200.f : 200.f) ,createPosition.y + (i % ((int)ActionKeyType::end / 2)) * 100.f });
		keyActionUIVector[i]->Start();
	}
}

void ControllerUIBar::SetActive(const bool active)
{
	UISpriteGameObject::SetActive(active);
	for (int i = 0; i < keyActionUIVector.size(); ++i)
	{
		keyActionUIVector[i]->SetActive(active);
	}
}

void ControllerUIBar::Start()
{
	UISpriteGameObject::Start();

	sortingOrder = 6;
	SetActive(false);
}
