#include "stdafx.h"
#include "SceneDev2.h"

#include "GameInclude.h"

void SceneDev2::CollisitionCheck()
{

	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Default, ColliderLayer::Player);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Wall, ColliderLayer::Player);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Enemy, ColliderLayer::Player);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Player, ColliderLayer::EnemyBullet);

	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Wall, ColliderLayer::Enemy);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Enemy, ColliderLayer::Enemy);

	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Item, ColliderLayer::Player);

	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Enemy, ColliderLayer::PlayerBullet);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Wall, ColliderLayer::PlayerBullet);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::SavePoint, ColliderLayer::Player);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::CleraPoint, ColliderLayer::Player);
}

void SceneDev2::Init()
{
	cameraLimitRect = { 0.f,13440.f,-500.f, 700.f };
	currentCameraLimitRect = cameraLimitRect;

	Scene::Init();
}

void SceneDev2::Enter()
{
	CameraManger::GetInstance().SetCamera(mainCamera);
	CameraManger::GetInstance().SetCamera(uICamera);

	TEXTURE_MANAGER.Load("Player", "graphics/player.png");
	TEXTURE_MANAGER.Load("enemies", "graphics/enemies.png");
	TEXTURE_MANAGER.Load("Items", "graphics/item_objects.png");
	TEXTURE_MANAGER.Load("tiles", "graphics/tiles.png");
	TEXTURE_MANAGER.Load("tile_set", "graphics/tile_set.png");
	TEXTURE_MANAGER.Load("mario_bros", "graphics/mario_bros.png");
	ResourcesManager<sf::Font>::GetInstance().Load("DungGeunMo", "fonts/DungGeunMo.ttf", true);

	Player* testPlayer = AddGameObject(new Player("Player"),LayerType::Player);
	testPlayer->Awake();
	mainCamera->SetFollowTarget(testPlayer, true);

	WallCollisionObject* wallCollision = AddGameObject(new WallCollisionObject, LayerType::Wall);
	wallCollision->SetScale({ 10000.f, 30.f });
	wallCollision->SetPosition({ 0, 100.f });
	BackgroundColorBox* background = AddGameObject(new BackgroundColorBox(), LayerType::Default);
	background->SetScale({ 2000.f, 1300.f });
	background->SetColor(sf::Color(85, 151, 248));

	EnemySpawner* enemySpawner = AddGameObject(new EnemySpawner(), LayerType::Default);
	enemySpawner->SetPosition({ 2000.f, 1300.f });

	CollisitionCheck();

	Scene::Enter();
}

void SceneDev2::Exit()
{
	Scene::Exit();
}

void SceneDev2::Release()
{
	Scene::Release();
}

void SceneDev2::Update(float dt)
{
	Scene::Update(dt);
}

void SceneDev2::Render(sf::RenderWindow& window)
{
	Scene::Render(window);
}

void SceneDev2::Save(const std::string& savePath)
{
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

			/*auto enemy = dynamic_cast<Enemy*>(gameObject);
			if (savePoint != nullptr)
			{
				data.enemySaveDatas.push_back(enemy->GetEnemySaveData());
				continue;
			}*/
			auto enemySpawner = dynamic_cast<EnemySpawner*>(gameObject);
			if (savePoint != nullptr)
			{
				data.enemySpawnerSaveDatas.push_back(enemySpawner->GetEnemySpawnerSaveData());
				continue;
			}
		}
	}
	SaveLoadManager::GetInstance().Save(data, savePath);
}

void SceneDev2::Load(const std::string& loadPath)
{
	SaveDataVC data = SaveLoadManager::GetInstance().Load(loadPath);

	Player* player = new Player();
	this->player = player;
	player->LoadData(data.playerData);
	player->Start();
	AddGameObject(player, player->GetLayerType());

	mainCamera->SetFollowTarget(player, true);
	mainCamera->SetCameraLimitRect(cameraLimitRect, true);


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
}

SceneDev2::SceneDev2()
	: Scene(SceneIds::SceneDev2)
	, player(nullptr)
{
	savePath = "stage2.json";
	loadPath = "stage2.json";
}

SceneDev2::~SceneDev2()
{
}
