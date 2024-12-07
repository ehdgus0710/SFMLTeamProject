#include "stdafx.h"
#include "SceneDev1.h"

#include "ScaffoldingObject.h"
#include "GameInclude.h"

#include "Yggdrasil.h"
#include "SkeletonSpear.h"

void SceneDev1::Init()
{
	Scene::Init();

	cameraLimitRect = { 0.f,13440.f,-500.f, 700.f };
	currentCameraLimitRect = cameraLimitRect;
}

void SceneDev1::Enter()
{
	CameraManger::GetInstance().SetCamera(mainCamera);
	CameraManger::GetInstance().SetCamera(uICamera);
	LoadResources(); 
	CollisitionCheck();


	//Player* testPlayer = AddGameObject(new Player("Player"), LayerType::Player);
	//testPlayer->Awake();
	//mainCamera->SetFollowTarget(testPlayer, true);
	//testPlayer->SetPosition({ 0, -500.f });
	//testPlayer->GetCollider()->SetScale({ 100.f,100.f });

	SkeletonSpear* testSkeletonSpear = AddGameObject(new SkeletonSpear("SkeletonSpear"), LayerType::Player);
	testSkeletonSpear->Awake();
	mainCamera->SetFollowTarget(testSkeletonSpear, true);
	testSkeletonSpear->SetPosition({ 0, -500.f });
	testSkeletonSpear->GetCollider()->SetScale({ 100.f,100.f });


	//Yggdrasil* testYggdrasil = AddGameObject(new Yggdrasil("Yggdrasil"), LayerType::Enemy);
	//testYggdrasil->Awake();
	//testYggdrasil->SetPosition({ 0, -350.f });
	//testYggdrasil->GetCollider()->SetScale({ 1000.f,1000.f });

	WallCollisionObject* wallCollision = AddGameObject(new WallCollisionObject, LayerType::Wall);
	wallCollision->SetScale({ 10000.f, 30.f });
	wallCollision->SetPosition({ 0, 100.f });

	ScaffoldingObject* scaffoldingObject = AddGameObject(new ScaffoldingObject("LittleBone_NonHead"), LayerType::Wall);
	scaffoldingObject->SetPosition({ 0, 400.f });

	BackgroundColorBox* background = AddGameObject(new BackgroundColorBox(), LayerType::Default);
	background->SetScale({ 2000.f, 1300.f });
	background->SetColor(sf::Color(85, 151, 248));

	Scene::Enter();
}

void SceneDev1::Exit()
{
	ImguiManger::GetInstance().Reset();
	Scene::Exit();

	CameraManger::GetInstance().Clear();
}

void SceneDev1::Release()
{
	Scene::Release();
}

void SceneDev1::Update(float dt)
{
	Scene::Update(dt);


}

void SceneDev1::Render(sf::RenderWindow& window)
{
	Scene::Render(window);
}

void SceneDev1::Save(const std::string& savePath)
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
			if (enemy != nullptr)
			{
				data.enemySaveDatas.push_back(enemy->GetEnemySaveData());
				continue;
			}*/
			auto enemySpawner = dynamic_cast<EnemySpawner*>(gameObject);
			if (enemySpawner != nullptr)
			{
				data.enemySpawnerSaveDatas.push_back(enemySpawner->GetEnemySpawnerSaveData());
				continue;
			}
		}
	}
	SaveLoadManager::GetInstance().Save(data, savePath);
}

void SceneDev1::Load(const std::string& loadPath)
{
	SaveDataVC data = SaveLoadManager::GetInstance().Load(loadPath);

	Player* player = new Player();
	this->player = player;
	player->LoadData(data.playerData);
	player->Start();
	AddGameObject(player, player->GetLayerType());

	mainCamera->SetFollowTarget(player, true);
	mainCamera->SetCameraLimitRect(cameraLimitRect, true);

	currentCameraLimitRect = cameraLimitRect;
	if (currentCameraLimitRect.leftPosition < player->GetPosition().x - 800.f)
	{
		currentCameraLimitRect.leftPosition = player->GetPosition().x - 800.f;
		mainCamera->SetCameraLimitRect(currentCameraLimitRect);
	}

	mainCamera->SetCameraPosition(player->GetPosition());

	for (const auto& data : data.wallCollisionSaveDatas)
	{
		WallCollisionObject* wall = new WallCollisionObject();
		wall->LoadWallCollisionSaveData(data);
		wall->Start();
		AddGameObject(wall, LayerType::Wall);
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
		if (player->GetPosition().x > data.gameObjectSaveData.position.x)
			continue;

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

void SceneDev1::CollisitionCheck()
{
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Default, ColliderLayer::Player);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Wall, ColliderLayer::Player);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Enemy, ColliderLayer::Player);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Player, ColliderLayer::EnemyBullet);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Player, ColliderLayer::Player);

	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Wall, ColliderLayer::PlayerHead);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Enemy, ColliderLayer::PlayerHead);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Boss, ColliderLayer::PlayerHead);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Reiana, ColliderLayer::PlayerHead);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Yggdrasil, ColliderLayer::PlayerHead);

	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Wall, ColliderLayer::Enemy);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Enemy, ColliderLayer::Enemy);

	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Scaffolding, ColliderLayer::Player);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Item, ColliderLayer::Player);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Item, ColliderLayer::Wall);

	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Enemy, ColliderLayer::PlayerBullet);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Wall, ColliderLayer::PlayerBullet);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::SavePoint, ColliderLayer::Player);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::CleraPoint, ColliderLayer::Player);
}

void SceneDev1::LoadResources()
{
	TEXTURE_MANAGER.Load("LittleBone_NonHead", "graphics/skul/LittleBone_NonHead.png");
	TEXTURE_MANAGER.Load("Little Bone", "graphics/skul/Little Bone.png");
}

SceneDev1::SceneDev1()
	: Scene(SceneIds::SceneDev1)
	, player(nullptr)
	, cameraWallCollisionObject(nullptr)
	, backgroundColorBox(nullptr)
{
	savePath = "stage1.json";
	loadPath = "stage1.json";
}

SceneDev1::~SceneDev1()
{
}
