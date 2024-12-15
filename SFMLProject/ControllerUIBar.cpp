#include "stdafx.h"
#include "ControllerUIBar.h"

#include "Scene.h"
#include "KeyActionUI.h"
#include "TextButton.h"
#include "Collider.h"

ControllerUIBar::ControllerUIBar(const std::string& texId, const std::string& name)
	: UISpriteGameObject(texId, name)
{
	CreateActionKeyUI();
}

void ControllerUIBar::CreateActionKeyUI()
{
	Scene* currentScene = SceneManager::GetInstance().GetCurrentScene();
	sf::Color defalutColor = { 98 , 73, 59, 255 };
	sf::Color selectionColor = { 174,151,133,255 };
	
	sf::Vector2f createPosition = { 920.f, 200.f };
	int keyHarpCount = (int)ActionKeyType::end / 2;
	for (int i = 0; i < (int)ActionKeyType::end; ++i)
	{
		switch ((ActionKeyType)i)
		{
		case ActionKeyType::LeftMove:
			keyActionUIVector.push_back(currentScene->AddGameObject(new KeyActionUI("LeftMove", ActionKeyType::LeftMove, "Status", "LeftMoveUI", 30, defalutColor, selectionColor), LayerType::UI));
			break;
		case ActionKeyType::RightMove:
			keyActionUIVector.push_back(currentScene->AddGameObject(new KeyActionUI("RightMove", ActionKeyType::RightMove, "Status", "RightMoveUI", 30, defalutColor, selectionColor), LayerType::UI));
			break;
		case ActionKeyType::Dash:
			keyActionUIVector.push_back(currentScene->AddGameObject(new KeyActionUI("Dash", ActionKeyType::Dash, "Status", "DashUI", 30, defalutColor, selectionColor), LayerType::UI));
			break;
		case ActionKeyType::Attack:
			keyActionUIVector.push_back(currentScene->AddGameObject(new KeyActionUI("Attack", ActionKeyType::Attack, "Status", "AttackUI", 30, defalutColor, selectionColor), LayerType::UI));
			break;
		case ActionKeyType::Skill1:
			keyActionUIVector.push_back(currentScene->AddGameObject(new KeyActionUI("Skill1", ActionKeyType::Skill1, "Status", "Skill1UI", 30, defalutColor, selectionColor), LayerType::UI));
			break;
		case ActionKeyType::Skill2:
			keyActionUIVector.push_back(currentScene->AddGameObject(new KeyActionUI("Skill2", ActionKeyType::Skill2, "Status", "Skill2UI", 30, defalutColor, selectionColor), LayerType::UI));
			break;
		case ActionKeyType::Jump:
			keyActionUIVector.push_back(currentScene->AddGameObject(new KeyActionUI("Jump", ActionKeyType::Jump, "Status", "JumpUI", 30, defalutColor, selectionColor), LayerType::UI));
			break;
		case ActionKeyType::ChangeSkul:
			keyActionUIVector.push_back(currentScene->AddGameObject(new KeyActionUI("ChangeSkul", ActionKeyType::ChangeSkul, "Status", "ChangeSkulUI", 30, defalutColor, selectionColor), LayerType::UI));
			break;
		case ActionKeyType::Item:
			keyActionUIVector.push_back(currentScene->AddGameObject(new KeyActionUI("Item", ActionKeyType::Item, "Status", "ItemUI", 30, defalutColor, selectionColor), LayerType::UI));
			break;
		case ActionKeyType::Down:
			keyActionUIVector.push_back(currentScene->AddGameObject(new KeyActionUI("Down", ActionKeyType::Down, "Status", "DownUI", 30, defalutColor, selectionColor), LayerType::UI));
			break;
		case ActionKeyType::end:
			break;
		default:
			break;
		}

		keyActionUIVector[i]->sortingOrder = 5;
		keyActionUIVector[i]->SetScale({ 3.f,3.f });
		keyActionUIVector[i]->SetPosition({ createPosition.x + (keyHarpCount > i ? -300.f : 700.f) ,createPosition.y + (i % ((int)ActionKeyType::end / 2)) * 100.f });
		keyActionUIVector[i]->Start();
	}

	resetButton = currentScene->AddGameObject(new TextButton("NameFont", "ResetButton", 40, defalutColor, selectionColor), LayerType::UI);
	resetButton->SetPosition(createPosition + sf::Vector2f::down * 640.f);
	resetButton->SetString(L"초기화");
	resetButton->GetCollider()->SetScale({ 1.75f, 1.5f });
	resetButton->GetCollider()->SetOffsetPosition({ 0.f , 7.5f });
	resetButton->SetButtonClickEvent(std::bind(&ControllerUIBar::OnResetKeyAction, this));


	returnButton = currentScene->AddGameObject(new TextButton("NameFont", "ReturnButton", 40, defalutColor, selectionColor), LayerType::UI);
	returnButton->SetPosition(createPosition + sf::Vector2f::down * 740.f);
	returnButton->SetString(L"돌아가기");
	returnButton->GetCollider()->SetScale({ 1.75f, 1.5f });
	returnButton->GetCollider()->SetOffsetPosition({ 0.f , 7.5f });

}

void ControllerUIBar::OnResetKeyAction()
{
	KeyActionManager::GetInstance().ResetActionKey();

	for (auto& actionKey : keyActionUIVector)
	{
		actionKey->OnResetActionKeyName();
	}
}

void ControllerUIBar::SetReturnClickEvent(std::function<void()> clickEvent)
{
	returnButtonClickEvent = clickEvent;
}

void ControllerUIBar::SetActive(const bool active)
{
	UISpriteGameObject::SetActive(active);
	for (int i = 0; i < keyActionUIVector.size(); ++i)
	{
		keyActionUIVector[i]->SetActive(active);
	}

	resetButton->SetActive(active);
	returnButton->SetActive(active);

}

void ControllerUIBar::Start()
{
	UISpriteGameObject::Start();

	sortingOrder = 6;
	SetActive(false);
	returnButton->SetButtonClickEvent(returnButtonClickEvent);
}
