#include "stdafx.h"
#include "TitleScene.h"

#include "TileMap.h"

#include "RectSpriteGameObject.h"
#include "MouseObject.h"
#include "UIButtonObject.h"
#include "TextButton.h"
#include "BackgroundColorBox.h"
#include "Collider.h"
#include "InGameUIHub.h"

#include "FadeOutUI.h"
#include "GameManager.h"

void TitleScene::Init()
{
	Scene::Init();
}

void TitleScene::Enter()
{
	GameManager::GetInstance().Reset();

	ResourcesManager<sf::Font>::GetInstance().Load("DungGeunMo", "fonts/DungGeunMo.ttf", true);
	ResourcesManager<sf::Texture>::GetInstance().Load("title_screen", "graphics/title_screen.png", true);
	TEXTURE_MANAGER.Load("Items", "graphics/item_objects.png");
	TEXTURE_MANAGER.Load("tiles", "graphics/tiles.png");
	TEXTURE_MANAGER.Load("tile_set", "graphics/tile_set.png");
	TEXTURE_MANAGER.Load("font", "graphics/font.png");

	fadeOutUI = AddGameObject(new FadeOutUI("FadeOut"), LayerType::UI);
	fadeOutUI->SetScale({ 3000.f, 3000.f });
	fadeOutUI->SetPosition({ 1000.f,1000.f });
	//fadeOut->SetOrigin(Origins)
	//fadeOutUI->SetActive(false);
	fadeOutUI->AddFadeOutEndEvent(std::bind(&TitleScene::StartGame, this));
	fadeOutUI->sortingOrder = -1;
	sf::Vector2f resolutionSize = sf::Vector2f(WindowManager::GetInstance().GetResolutionSize());


	BackgroundColorBox* background = AddGameObject(new BackgroundColorBox(), LayerType::Default);
	background->SetScale({ 2000.f, 1300.f });
	background->SetColor(sf::Color(85, 151, 248));


	RectSpriteGameObject* titleSprite = AddGameObject(new RectSpriteGameObject({ 1, 60, 176, 88 }, "title_screen", "TitleSprite"), LayerType::UI);
	titleSprite->SetPosition({ resolutionSize.x * 0.5f , resolutionSize.y * 0.35f });
	titleSprite->SetScale(sf::Vector2f::one * 5.f);

	MouseObject* mouse = AddGameObject(new MouseObject(), LayerType::UI);

	TextButton* button = AddGameObject(new TextButton("DungGeunMo", "Start Button", 100), LayerType::InGameUI);
	button->SetOrigin(Origins::MiddleCenter);
	button->SetPosition({ resolutionSize.x * 0.5f , resolutionSize.y * 0.6f });
	button->SetString("Start Button");
	button->SetButtonClickEvent(std::bind(&FadeOutUI::StartFadeOut, fadeOutUI));
	button->GetCollider()->SetOffsetPosition({ 0.f, 50.f });

	TextButton* endButton = AddGameObject(new TextButton("DungGeunMo", "End Button", 100), LayerType::InGameUI);
	endButton->SetOrigin(Origins::MiddleCenter);
	endButton->SetPosition({ resolutionSize.x * 0.5f , resolutionSize.y * 0.75f });
	endButton->SetString("End Button");
	endButton->SetButtonClickEvent(std::bind(&TitleScene::EndGame, this));
	endButton->GetCollider()->SetOffsetPosition({ 0.f, 50.f });

	TileMap* tilemap = AddGameObject(new TileMap("",""), LayerType::TileMap);
	tilemap->LoadCsv("tileMap/Stage1TileMap1.csv");
	tilemap->SetPosition(sf::Vector2f::down * -64.f);

	InGameUIHub* uiHub = AddGameObject(new InGameUIHub("DungGeunMo", "UIHub"), LayerType::UI);

	CollisitionCheck();

	Scene::Enter();

	// fadeOutUI->SetActive(false);
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

	if (isStartGame)
		SceneManager::GetInstance().ChangeScene(SceneIds::SceneDev1);
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

void TitleScene::CollisitionCheck()
{
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::UI, ColliderLayer::UI);
}

void TitleScene::StartGame()
{
	isStartGame = true;
}

void TitleScene::EndGame()
{
	isEndGame = true;
	WindowManager::GetInstance().GetRenderWindow()->close();
}

TitleScene::TitleScene()
	: Scene(SceneIds::SceneDev2)
	, isStartGame(false)
	, isEndGame(false)
	, fadeOutUI(nullptr)
{

}

TitleScene::~TitleScene()
{
}
