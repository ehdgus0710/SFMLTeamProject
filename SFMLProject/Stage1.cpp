#include "stdafx.h"
#include "Stage1.h"

#include "ScaffoldingObject.h"
#include "GameInclude.h"

#include "Yggdrasil.h"

#include "GameInclude.h"
#include "Animation.h"
#include "BackgroundSprite.h"
#include "PlayerUIHub.h"

#include "Yggdrasil.h"
#include "YggdrasilUIHub.h"
#include "SkillCoolTimeUI.h"
#include "PauseUIBar.h"
#include "DoorObject.h"

Stage1::Stage1()
	: Scene(SceneIds::Stage1)
	, pauseUIBar(nullptr)
{
	savePath = "Stage1.json";
	loadPath = "Stage1.json";


	cameraLimitRect = { -400.f, 2340.f,-1000.f, 1080.f };
	currentCameraLimitRect = cameraLimitRect;
}

Stage1::~Stage1()
{
}

void Stage1::CollisitionCheck()
{
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Default, ColliderLayer::Player);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Wall, ColliderLayer::Player);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Enemy, ColliderLayer::Player);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Player, ColliderLayer::EnemyBullet);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Player, ColliderLayer::Boss);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Wall, ColliderLayer::EnemyBullet);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Player, ColliderLayer::PlayerHead);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Door, ColliderLayer::Player);

	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Wall, ColliderLayer::Enemy);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Enemy, ColliderLayer::Enemy);

	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Item, ColliderLayer::Player);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Wall, ColliderLayer::Reiana);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::PlayerBullet, ColliderLayer::Reiana);

	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Wall, ColliderLayer::PlayerHead);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Enemy, ColliderLayer::PlayerHead);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Boss, ColliderLayer::PlayerHead);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Reiana, ColliderLayer::PlayerHead);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Yggdrasil, ColliderLayer::PlayerHead);

	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Boss, ColliderLayer::Player);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Boss, ColliderLayer::PlayerBullet);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Enemy, ColliderLayer::PlayerBullet);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Wall, ColliderLayer::PlayerBullet);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::SavePoint, ColliderLayer::Player);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::CleraPoint, ColliderLayer::Player);

	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::UI, ColliderLayer::UI);
}

void Stage1::LoadResources()
{
	ResourcesManager<sf::Font>::GetInstance().Load("Status", "fonts/Perfect DOS VGA 437.ttf", true);
	ResourcesManager<sf::Font>::GetInstance().Load("NameFont2", "fonts/NotoSans-Bold.ttf", true);
	ResourcesManager<sf::Font>::GetInstance().Load("NameFont", "fonts/D2Coding.ttc", true);

	// map
	TEXTURE_MANAGER.Load("Stage1TileMap", "graphics/TileMap/1_Tile01.png");
	TEXTURE_MANAGER.Load("bossidle", "graphics/objects/bossidle.png");
	TEXTURE_MANAGER.Load("KeyF", "graphics/UI/Key/F.png");

	// Background
	TEXTURE_MANAGER.Load("lobbyBackground", "graphics/backgrounds/lobbyBackground.png");
	TEXTURE_MANAGER.Load("lobby", "graphics/backgrounds/lobby.png");
	TEXTURE_MANAGER.Load("lobbyBackColor", "graphics/backgrounds/08.png");
	TEXTURE_MANAGER.Load("DuegenEntrance", "graphics/backgrounds/Duegen_Entrance.png");
	
	// Player UI
	TEXTURE_MANAGER.Load("PlayerUiFrame", "graphics/UI/PlayerUI/player_ui_frame.png");
	TEXTURE_MANAGER.Load("SkulSimbul", "graphics/UI/PlayerUI/Skul.png");
	TEXTURE_MANAGER.Load("SkullThrow", "graphics/UI/PlayerUI/skull_throw.png");
	TEXTURE_MANAGER.Load("Rebone", "graphics/UI/PlayerUI/rebone.png");
	TEXTURE_MANAGER.Load("PlayerHealthBar", "graphics/UI/PlayerUI/Player_HealthBar.png");

}

void Stage1::SetChangeScene(SceneIds id)
{
	if (isChangeScene)
		return;

	changeSceneIds = id;
	isChangeScene = true;
}

void Stage1::Init()
{
	TEXTURE_MANAGER.Load("LittleBone_NonHead", "graphics/skul/LittleBone_NonHead.png");
	TEXTURE_MANAGER.Load("Little Bone", "graphics/skul/Little Bone.png");
	TEXTURE_MANAGER.Load("LittleBoneSkill", "graphics/skul/LittleBoneSkill.png");
	TEXTURE_MANAGER.Load("PlayerHitEffect", "graphics/effects/HitEffect.png");
	TEXTURE_MANAGER.Load("NormalAttack", "graphics/effects/Normal_Attack.png");

	Scene::Init();
}

void Stage1::Enter()
{
	ResourcesManager<sf::Texture>::GetInstance().Load("SkulSpear", "graphics/skul/SkulSpear.png", true);
	CameraManger::GetInstance().SetCamera(mainCamera);
	CameraManger::GetInstance().SetCamera(uICamera);
	LoadResources();
	CollisitionCheck();

	BackgroundSprite* backgroundObject = AddGameObject(new BackgroundSprite("lobbyBackground", "lobbyBackground"), LayerType::BackGround_Back);

	backgroundObject->SetScale({ 2.f, 2.f });
	backgroundObject->SetOrigin(Origins::MiddleCenter);
	backgroundObject->SetPosition({ 960.f, -260.f });
	backgroundObject->sortingOrder = 3;

	SpriteGameObject* background = AddGameObject(new BackgroundSprite("lobby", "lobby"), LayerType::BackGround_Back);
	background->SetScale({ 3.f, 3.f });
	background->SetOrigin(Origins::MiddleCenter);
	background->SetPosition({ 1200.f, -160.f });
	background->sortingOrder = 2;

	SpriteGameObject* duegenEntrance = AddGameObject(new BackgroundSprite("DuegenEntrance", "DuegenEntrance"), LayerType::TileMap);
	duegenEntrance->SetScale({ 3.f, 3.f });
	duegenEntrance->SetOrigin(Origins::MiddleCenter);
	duegenEntrance->SetPosition({ 960.f, 40.f });
	/*TileMapController* tilemapController = AddGameObject(new TileMapController("Stage1"), LayerType::TileMap);
	tilemapController->SetSpriteSheetId("Stage1TileMap");
	tilemapController->SetCellSize({ 32.f,32.f });*/

	SpriteGameObject* backColor = AddGameObject(new BackgroundSprite("lobbyBackColor", "lobbyBackColor"), LayerType::BackGround_Back);
	backColor->SetScale({ 3.f, 3.f });
	backColor->SetOrigin(Origins::MiddleCenter);
	backColor->SetPosition({ 1200.f, 0.f });
	backColor->sortingOrder = 4;

	/*TileMap* tileMap = AddGameObject(new TileMap("Stage1TileMap", "Stage1TileMap"), LayerType::TileMap);
	tileMap->SetTileInfo("Stage1TileMap", { 16,16 }, { 32.f,32.f }, { 32,32 });*/
	// tileMap->LoadCsv("TileMap/Stage1Map1.csv");

	WallCollisionObject* wallObject = AddGameObject(new WallCollisionObject("Wall1"), LayerType::Wall);
	wallObject->SetPosition({ 1182.f, 1300.f });
	wallObject->SetScale({ 3280.f, 960.f });
	wallObject->SetOrigin(Origins::MiddleCenter);

	WallCollisionObject* leftWallObject = AddGameObject(new WallCollisionObject("leftWallObject"), LayerType::Wall);
	leftWallObject->SetPosition({ -464.f, -32.f });
	leftWallObject->SetScale({ 96.f, 2304.f });
	leftWallObject->SetOrigin(Origins::MiddleCenter);

	WallCollisionObject* rightWallObject = AddGameObject(new WallCollisionObject("rightWallObject"), LayerType::Wall);
	rightWallObject->SetPosition({ 2448.f, 384.f });
	rightWallObject->SetScale({ 192.f, 1600.f });
	rightWallObject->SetOrigin(Origins::MiddleCenter);

	Player* testPlayer = AddGameObject(new Player("Player"), LayerType::Player);
	testPlayer->Awake();
	testPlayer->SetPosition({ 0, -500.f });
	testPlayer->GetCollider()->SetScale({ 30.f,30.f });

	DoorObject* doorObject = AddGameObject(new DoorObject("KeyF",SceneIds::Stage2, "Boos1Door"), LayerType::BackGround_Forward);
	doorObject->SetPosition({ 765.f, 582.f });

	DoorObject* boos2Door = AddGameObject(new DoorObject("KeyF", SceneIds::Stage3, "Boos2Door"), LayerType::BackGround_Forward);
	boos2Door->SetPosition({ 1800.f, 582.f });

	mainCamera->SetFollowTarget(testPlayer, true);
	mainCamera->SetCameraLimitRect(currentCameraLimitRect);
	mainCamera->SetCameraPosition(testPlayer->GetPosition());

	pauseUIBar = AddGameObject(new PauseUIBar("PauseFrame", "PauseFrame"), LayerType::UI);
	pauseUIBar->SetScale({ 3.f,3.f });
	pauseUIBar->SetPosition({ mainCamera->GetView().getSize().x * 0.5f, 450.f });

	Scene::Enter();
}

void Stage1::Exit()
{
	Scene::Exit();
}

void Stage1::Release()
{
	Scene::Release();
}

void Stage1::Update(float dt)
{
	Scene::Update(dt);

	if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::Escape))
	{
		pauseUIBar->SetActive(!pauseUIBar->IsActive());
	}

	if (isChangeScene)
	{
		isChangeScene = false;
		SceneManager::GetInstance().ChangeScene(changeSceneIds);
	}
}

void Stage1::Render(sf::RenderWindow& window)
{
	Scene::Render(window);
}

void Stage1::Save(const std::string& savePath)
{
	/*
	SaveDataVC data;

	data.playerData = ((Player*)FindGameObject("Player"))->GetPlayerSaveData();

	for (auto& gameObjects : gameObjectVectors)
	{
		for (auto& gameObject : gameObjects)
		{
			auto tileMapController = dynamic_cast<TileMapController*>(gameObject);
			if (tileMapController != nullptr)
			{
				data.tileMapSaveData = tileMapController->GetTileMapSaveData();
				continue;
			}

			auto wallCollision = dynamic_cast<WallCollisionObject*>(gameObject);
			if (wallCollision != nullptr)
			{
				data.wallCollisionSaveDatas.push_back(wallCollision->GetWallCollisionSaveData());
				continue;
			}
			auto savePoint = dynamic_cast<SavePointObject*>(gameObject);
			if (savePoint != nullptr)
			{
				data.savePointSaveDatas.push_back(savePoint->GetSavePointSaveData());
				continue;
			}

			// auto enemy = dynamic_cast<Enemy*>(gameObject);
			// if (savePoint != nullptr)
			// {
			// 	  data.enemySaveDatas.push_back(enemy->GetEnemySaveData());
			// 	  continue;
			// }
			auto enemySpawner = dynamic_cast<EnemySpawner*>(gameObject);
			if (savePoint != nullptr)
			{
				data.enemySpawnerSaveDatas.push_back(enemySpawner->GetEnemySpawnerSaveData());
				continue;
			}
		}
	}
	SaveLoadManager::GetInstance().Save(data, savePath);
	*/
}

void Stage1::Load(const std::string& loadPath)
{

	/*
	SaveDataVC data = SaveLoadManager::GetInstance().Load(loadPath);

	//Player* player = new Player();
	//this->player = player;
	//player->LoadData(data.playerData);
	//player->Start();
	//AddGameObject(player, player->GetLayerType());

	//mainCamera->SetFollowTarget(player, true);
	//mainCamera->SetCameraLimitRect(cameraLimitRect, true);


	for (const auto& data : data.wallCollisionSaveDatas)
	{
		WallCollisionObject* wall = new WallCollisionObject();
		wall->LoadWallCollisionSaveData(data);
		wall->Start();
		AddGameObject(wall, wall->GetLayerType());
	}

	TileMapController* tileMapController = new TileMapController("");
	tileMapController->LoadTileMapSaveData(data.tileMapSaveData);
	tileMapController->Start();
	AddGameObject(tileMapController, tileMapController->GetLayerType());


	for (const auto& data : data.savePointSaveDatas)
	{
		SavePointObject* savePointObject = new SavePointObject();
		savePointObject->LoadSavePointSaveData(data);
		savePointObject->Start();
		AddGameObject(savePointObject, savePointObject->GetLayerType());
	}
	for (const auto& data : data.enemySaveDatas)
	{
		switch ((EnemyType)data.enemyType)
		{
		case EnemyType::End:
			break;
		default:
			break;
		}
	}

	for (const auto& data : data.enemySpawnerSaveDatas)
	{
		EnemySpawner* enemySpawner = new EnemySpawner();
		enemySpawner->LoadEnemySpawnerSaveData(data);
		enemySpawner->Start();
		AddGameObject(enemySpawner, enemySpawner->GetLayerType());
	}
	*/
}