#include "stdafx.h"
#include "PauseUIBar.h"

#include "UITextGameObject.h"
#include "TextButton.h"
#include "Scene.h"
#include "MouseObject.h"
#include "Collider.h"
#include "SettingUIBar.h"
#include "BackgroundColorBox.h"


PauseUIBar::PauseUIBar(const std::string& texId, const std::string& name)
	: UISpriteGameObject(texId, name)
	, pauseText(nullptr)
	, goBackButton(nullptr)
	, newGameButton(nullptr)
	, controllerButton(nullptr)
	, settingButton(nullptr)
	, endGameButton(nullptr)
	, mouseObject(nullptr)
	, settingUIBar(nullptr)

{
	prevTimeScale = TimeManager::GetInstance().GetTimeScale();
	InputManager::GetInstance().BindKey(sf::Keyboard::Escape);
}

void PauseUIBar::OffUIBar()
{
	SetActive(false);
}

void PauseUIBar::OnNewGame()
{
}

void PauseUIBar::OnControllerBar()
{
}

void PauseUIBar::OnSettingBar()
{
	settingUIBar->SetActive(true);

	for (auto& button : buttons)
	{
		button->SetActive(false);
		button->GetCollider()->SetActive(false);
	}
}

void PauseUIBar::OffSettingBar()
{
	settingUIBar->SetActive(false);

	for (auto& button : buttons)
	{
		button->SetActive(true);
	}
}

void PauseUIBar::OnEndGame()
{
	WindowManager::GetInstance().GetRenderWindow()->close();
}

void PauseUIBar::CreateUIObject()
{
	Scene* currentScene = SceneManager::GetInstance().GetCurrentScene();

	backgroundRect = currentScene->AddGameObject(new BackgroundColorBox(), LayerType::UI);
	backgroundRect->SetColor(sf::Color::Black - sf::Color(0, 0, 0, 80.f));
	backgroundRect->SetScale({ 3000.f, 2000.f });
	backgroundRect->Start();

	backgroundRect->sortingOrder = 12;

	sf::Vector2f pos = { position.x, 340.f };
	pauseText = currentScene->AddGameObject(new UITextGameObject("NameFont", "pauseText", 30, { 174,151,133,255 }), LayerType::UI);
	pauseText->SetPosition(pos);
	pauseText->SetOrigin(Origins::MiddleCenter);
	pauseText->SetString(L"일시정지");
	pauseText->Start();

	goBackButton = currentScene->AddGameObject(new TextButton("NameFont", "NewGameButton", 30, { 98 , 73, 59, 255 }, { 174,151,133,255 }), LayerType::UI);
	goBackButton->SetString(L"돌아가기");
	goBackButton->SetOrigin(Origins::MiddleCenter);
	goBackButton->SetPosition(pos + sf::Vector2f::down * 120.f);
	goBackButton->GetCollider()->SetScale({ 1.75f, 1.5f });
	goBackButton->GetCollider()->SetOffsetPosition({ 0.f , 7.5f });
	goBackButton->Start();
	goBackButton->SetButtonClickEvent(std::bind(&PauseUIBar::OffUIBar, this));

	newGameButton = currentScene->AddGameObject(new TextButton("NameFont", "NewGameButton", 30, { 98 , 73, 59, 255 }, { 174,151,133,255 }), LayerType::UI);
	newGameButton->SetString(L"새 게임");
	newGameButton->SetOrigin(Origins::MiddleCenter);
	newGameButton->SetPosition(pos + sf::Vector2f::down * 180.f);
	newGameButton->GetCollider()->SetScale({ 1.75f, 1.5f });
	newGameButton->GetCollider()->SetOffsetPosition({ 0.f , 7.5f });
	newGameButton->Start();
	newGameButton->SetButtonClickEvent(std::bind(&PauseUIBar::OnNewGame, this));

	controllerButton = currentScene->AddGameObject(new TextButton("NameFont", "ControllerButton", 30, { 98 , 73, 59, 255 }, { 174,151,133,255 }), LayerType::UI);
	controllerButton->SetString(L"컨트롤");
	controllerButton->SetOrigin(Origins::MiddleCenter);
	controllerButton->SetPosition(pos + sf::Vector2f::down * 240.f);
	controllerButton->GetCollider()->SetScale({ 1.75f, 1.5f });
	controllerButton->GetCollider()->SetOffsetPosition({ 0.f , 7.5f });
	controllerButton->Start();
	controllerButton->SetButtonClickEvent(std::bind(&PauseUIBar::OnControllerBar, this));

	settingButton = currentScene->AddGameObject(new TextButton("NameFont", "SettingButton", 30, { 98 , 73, 59, 255 }, { 174,151,133,255 }), LayerType::UI);
	settingButton->SetString(L"설정");
	settingButton->SetOrigin(Origins::MiddleCenter);
	settingButton->SetPosition(pos + sf::Vector2f::down * 300.f);
	settingButton->GetCollider()->SetScale(sf::Vector2f::one * 1.5f);
	settingButton->GetCollider()->SetOffsetPosition({ 0.f , 7.5f });
	settingButton->Start();
	settingButton->SetButtonClickEvent(std::bind(&PauseUIBar::OnSettingBar, this));


	endGameButton = currentScene->AddGameObject(new TextButton("NameFont", "EndGameButton", 30, { 98 , 73, 59, 255 }, { 174,151,133,255 }), LayerType::UI);
	endGameButton->SetString(L"게임종료");
	endGameButton->SetOrigin(Origins::MiddleCenter);
	endGameButton->SetPosition(pos + sf::Vector2f::down * 360.f);
	endGameButton->GetCollider()->SetScale({ 1.75f, 1.5f });
	endGameButton->GetCollider()->SetOffsetPosition({ 0.f , 7.5f });
	endGameButton->Start();
	endGameButton->SetButtonClickEvent(std::bind(&PauseUIBar::OnEndGame, this));

	mouseObject = currentScene->AddGameObject(new MouseObject(), LayerType::UI);
	mouseObject->Start();

	settingUIBar = currentScene->AddGameObject(new SettingUIBar("OptionsFrame", "SettingUIBar"), LayerType::UI);
	settingUIBar->SetPosition({ 960.f, 550.f });
	settingUIBar->SetScale({ 3.f,3.f });
	settingUIBar->SetReturnClickEvent(std::bind(&PauseUIBar::OffSettingBar, this));

	buttons.push_back(goBackButton);
	buttons.push_back(controllerButton);
	buttons.push_back(newGameButton);
	buttons.push_back(endGameButton);
	buttons.push_back(settingButton);
}

void PauseUIBar::SetChildActive(const bool active)
{
	pauseText->SetActive(active);
	newGameButton->SetActive(active);
	controllerButton->SetActive(active);
	settingButton->SetActive(active);
	endGameButton->SetActive(active);
	goBackButton->SetActive(active);
	mouseObject->SetActive(active);
	backgroundRect->SetActive(active);
}

void PauseUIBar::SetActive(const bool active)
{
	if (active)
	{
		InputManager::GetInstance().SetInputable(active);
		prevTimeScale = TimeManager::GetInstance().GetTimeScale();
		TimeManager::GetInstance().SetTimeScale(0.f);

		this->active = active;
		SetChildActive(active);
		settingUIBar->SetActive(false);
	}
	else
	{
		if (settingUIBar->IsActive())
		{
			OffSettingBar();
		}
		else
		{
			InputManager::GetInstance().SetInputable(active);
			TimeManager::GetInstance().SetTimeScale(prevTimeScale);

			this->active = active;
			SetChildActive(active);
		}
	}
}

void PauseUIBar::Start()
{
	UISpriteGameObject::Start();
	CreateUIObject();

	sortingOrder = 11;
	pauseText->sortingOrder = 10;

	settingUIBar->SetActive(false);
	SetActive(false);
}
