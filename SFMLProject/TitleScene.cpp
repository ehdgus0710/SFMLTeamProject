#include "stdafx.h"
#include "TitleScene.h"

#include "RectSpriteGameObject.h"
#include "MouseObject.h"
#include "UIButtonObject.h"
#include "TextButton.h"
#include "Collider.h"
#include "InGameUIHub.h"

#include "FadeOutUI.h"
#include "UIFadeInOutSpriteObject.h"
#include "UIFadeTextGameObject.h"


TitleScene::TitleScene()
	: Scene(SceneIds::SceneDev2)
	, isStartGame(false)
	, isStartGameFade(false)
	, fadeOutUI(nullptr)
	, titleSprite(nullptr)
	, titleLogo(nullptr)
	, messageText(nullptr)


{

}

TitleScene::~TitleScene()
{
}

void TitleScene::Init()
{
	Scene::Init();
	KeyActionManager::GetInstance().Init();
}

void TitleScene::Enter()
{
	KeyActionManager::GetInstance().LoadCSV();
	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("Adventurer", "AudioClip/Title/Adventurer.wav");

	ResourcesManager<sf::Font>::GetInstance().Load("NameFont", "fonts/D2Coding.ttc", true);
	ResourcesManager<sf::Font>::GetInstance().Load("DungGeunMo", "fonts/DungGeunMo.ttf", true);
	ResourcesManager<sf::Texture>::GetInstance().Load("TitleScreen", "graphics/UI/Title/Title_Art2.png", true);
	ResourcesManager<sf::Texture>::GetInstance().Load("TitleLogo", "graphics/UI/Title/Title_Logo2.png", true);

	
	ResourcesManager<sf::Texture>::GetInstance().Load("Bossidle", "graphics/objects/bossidle.png", true);

	fadeOutUI = AddGameObject(new FadeOutUI("FadeOut"), LayerType::UI);
	fadeOutUI->SetScale({ 3000.f, 3000.f });
	fadeOutUI->SetPosition({ 1000.f,1000.f });
	fadeOutUI->AddFadeOutEndEvent(std::bind(&TitleScene::StartGame, this));
	fadeOutUI->sortingOrder = -1;
	fadeOutUI->StartFadeIn(1.f);
	sf::Vector2f resolutionSize = sf::Vector2f(WindowManager::GetInstance().GetResolutionSize());
	fadeOutUI->AddFadeInEndEvent(std::bind(&TitleScene::OnStartFadeInEvent, this));


	titleSprite = AddGameObject(new SpriteGameObject("TitleScreen", "TitleScreen"), LayerType::UI);
	titleSprite->SetPosition({ resolutionSize.x * 0.5f , resolutionSize.y * 0.5f });
	titleSprite->SetScale(sf::Vector2f::one * 0.75f);
	titleSprite->SetOrigin(Origins::MiddleCenter);

	titleLogo = AddGameObject(new UIFadeInOutSpriteObject("TitleLogo", "TitleLogo"), LayerType::UI);
	titleLogo->SetPosition({ resolutionSize.x * 0.5f , resolutionSize.y * 0.5f });
	titleLogo->SetScale(sf::Vector2f::one * 0.75f);
	titleLogo->SetOrigin(Origins::MiddleCenter);
	titleLogo->SetActive(false);

	messageText = AddGameObject(new UIFadeTextGameObject("NameFont", "InputKeyText",40, { 142 , 109 ,231, 255}), LayerType::UI);
	messageText->SetString(L"아무 키나 누르세요");	
	messageText->SetPosition({ resolutionSize.x * 0.5f , resolutionSize.y * 0.9f });
	messageText->SetOrigin(Origins::MiddleCenter);
	messageText->SetActive(false);

	MouseObject* mouse = AddGameObject(new MouseObject(), LayerType::UI);

	CollisitionCheck();

	Scene::Enter();

	SoundManger::GetInstance().PlayBgm("Adventurer");
}

void TitleScene::Exit()
{
	isStartGame = false;
	Scene::Exit();
}

void TitleScene::Release()
{
	Scene::Release();
}

void TitleScene::Update(float dt)
{
	Scene::Update(dt);

	if (!isStartGameFade && messageText->IsActive() && InputManager::GetInstance().GetInputKey())
	{
		isStartGameFade = true;
		fadeOutUI->StartFadeOut();
		fadeOutUI->AddFadeOutEndEvent(std::bind(&TitleScene::StartGame, this));
	}
	if (isStartGame)
	{
		SceneManager::GetInstance().ChangeScene(SceneIds::Stage1);
	}
}

void TitleScene::Render(sf::RenderWindow& window)
{
	Scene::Render(window);
}

void TitleScene::Save(const std::string& savePath)
{
}

void TitleScene::Load(const std::string& loadPath)
{
}

void TitleScene::OnStartFadeInEvent()
{
	titleLogo->SetActive(true);
	titleLogo->StartFadeOut();
	messageText->SetActive(true);
	OnTextFadeIn();
}

void TitleScene::OnTextFadeIn()
{
	messageText->StartFadeIn(1.5f);
	messageText->AddFadeInEndEvent(std::bind(&TitleScene::OnTextFadeOut, this));
}

void TitleScene::OnTextFadeOut()
{
	messageText->StartFadeOut(1.5f);
	messageText->AddFadeOutEndEvent(std::bind(&TitleScene::OnTextFadeIn, this));
}

void TitleScene::CollisitionCheck()
{
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::UI, ColliderLayer::UI);
}

void TitleScene::StartGame()
{
	isStartGame = true;
}