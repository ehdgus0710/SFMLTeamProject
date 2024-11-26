#include "stdafx.h"
#include "SceneDev2.h"

#include "GameInclude.h"

void SceneDev2::CollisitionCheck()
{

	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Default, ColliderLayer::Player);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Wall, ColliderLayer::Player);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Block, ColliderLayer::Player);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Enemy, ColliderLayer::Player);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Player, ColliderLayer::EnemyBullet);

	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Wall, ColliderLayer::Enemy);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Block, ColliderLayer::Enemy);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Enemy, ColliderLayer::Enemy);

	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Item, ColliderLayer::Player);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Item, ColliderLayer::Block);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Item, ColliderLayer::Wall);

	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Enemy, ColliderLayer::PlayerBullet);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Wall, ColliderLayer::PlayerBullet);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Block, ColliderLayer::PlayerBullet);
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

	Koopa* koopa = AddGameObject(new Koopa(), LayerType::Enemy);
	koopa->Awake();
	koopa->SetPosition({300.f, 20.f});

	/*Goomba* enemy = AddGameObject(new Goomba(), LayerType::Enemy);
	enemy->SetPosition(testPlayer->GetPosition() + sf::Vector2f::left * 500.f);

	KoopaTroopa* koopaTroopa = AddGameObject(new KoopaTroopa(), LayerType::Enemy);
	koopaTroopa->SetPosition(testPlayer->GetPosition() + sf::Vector2f::left * 800.f);*/
	
	////auto animator = testPlayer->GetAnimator();
	////animator->AddAnimation(&ResourcesManager<Animation>::GetInstance().Get("marioIdle"), "marioIdle");

	//// Goomba* enemy = AddGameObject(new Goomba(), LayerType::Enemy);
	//// enemy->SetPosition(testPlayer->GetPosition() + sf::Vector2f::left * 300.f);
	//// mainCamera->SetCameraLimitRect({ -2000.f, 2000.f, -2000.f, 2000.f });

	////TileMap* tile = AddGameObject(new TileMap("tiles", "Map"), LayerType::TileMap);
	////tile->SetTileInfo("tiles", { 30,30 }, { 64.f,64.f }, { 32,32 });
	////tile->SaveCsv("TileMap/test.csv");
	////tile->LoadCsv("TileMap/test.csv");
	//ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Enemy, ColliderLayer::Player);

	////BlockObject* block = AddGameObject(new BlockObject(BlockType::Brick ,"tile_set"), LayerType::Block);

	//BrickBlockObject* brickBlock = AddGameObject(new BrickBlockObject("tile_set"), LayerType::Block); 
	//brickBlock->SetPosition({ 100.f, -150.f });

	WallCollisionObject* wallCollision = AddGameObject(new WallCollisionObject, LayerType::Wall);
	wallCollision->SetScale({ 10000.f, 30.f });
	wallCollision->SetPosition({ 0, 100.f });

	////  ItemBlockObject* block = AddGameObject(new ItemBlockObject(ItemType::MushRoom, "tile_set", "tile_set"), LayerType::Block);

	//TileMapController* tileMapController = AddGameObject(new TileMapController("TileMapController"), LayerType::Default);

	//CoinObject* coin = AddGameObject(new CoinObject, LayerType::Item);
	//coin->SetPosition({ -100.f, -150.f });
	//StarObject* star = AddGameObject(new StarObject, LayerType::Item);
	//star->SetPosition({ -150.f, -150.f });
	//FlowerObject* flower = AddGameObject(new FlowerObject, LayerType::Item);
	//flower->SetPosition({ -200.f, -150.f });
	//MushRoomObject* mushroom = AddGameObject(new MushRoomObject, LayerType::Item);
	//mushroom->SetPosition({ -250.f, -150.f });

	// InGameUIHub* uiHub = AddGameObject(new InGameUIHub("DungGeunMo", "UIHub"), LayerType::UI);


	BackgroundColorBox* background = AddGameObject(new BackgroundColorBox(), LayerType::Default);
	background->SetScale({ 2000.f, 1300.f });
	background->SetColor(sf::Color(85, 151, 248));

	EnemySpawner* enemySpawner = AddGameObject(new EnemySpawner(), LayerType::Default);
	enemySpawner->SetPosition({ 2000.f, 1300.f });

	LabberObject* laberObject = AddGameObject(new LabberObject({ 0, 8 * 16,16,16 }, "Items", "labber"), LayerType::Default);
	laberObject->SetPosition({ 500.f, 0.f });

	CollisitionCheck();
	// KooparHammerBullet* kooparHammerBullet = AddGameObject(new KooparHammerBullet(), LayerType::Default);
	// kooparHammerBullet->SetPosition({ 100.f, 0.f });
	/*GameClearObject* gameClearObject = AddGameObject(new GameClearObject(), LayerType::CleraPoint);
	gameClearObject->SetScale({ 10.f, 1300.f });
	gameClearObject->SetPosition({ 800.f, 0.f });
	gameClearObject->SetDestinationPosition({ 800.f, 440 });
	gameClearObject->SetMaxStartPosition({ 800.f, -440 });
	gameClearObject->SetEndMovePosition({ 1700.f, 440 });*/

	// SavePointObject* savePoint = AddGameObject(new SavePointObject(), LayerType::Default);

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

			auto blockObject = dynamic_cast<BlockObject*>(gameObject);
			if (blockObject != nullptr)
			{

				if (blockObject->GetBlockType() == BlockType::Item || blockObject->GetBlockType() == BlockType::ItemBrick)
				{
					data.itemBlockSaveDatas.push_back(((ItemBlockObject*)blockObject)->GetItemBlockSaveData());
				}
				else
				{
					data.blockSaveDatas.push_back(blockObject->GetBlockSaveDate());
				}
				continue;
			}

			auto savePoint = dynamic_cast<SavePointObject*>(gameObject);
			if (savePoint != nullptr)
			{
				data.savePointSaveDatas.push_back(savePoint->GetSavePointSaveData());
				continue;
			}

			auto gameClearObject = dynamic_cast<GameClearObject*>(gameObject);
			if (savePoint != nullptr)
			{
				data.gameClearSaveDatas.push_back(gameClearObject->GetGameClearSaveData());
				continue;
			}

			auto enemy = dynamic_cast<Enemy*>(gameObject);
			if (savePoint != nullptr)
			{
				data.enemySaveDatas.push_back(enemy->GetEnemySaveData());
				continue;
			}
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

	for (const auto& data : data.blockSaveDatas)
	{
		BlockObject* newBlock = nullptr;
		switch ((BlockType)data.blockType)
		{
		case BlockType::Default:
		{
			newBlock = new BlockObject(BlockType::Default, "");
		}
		break;
		case BlockType::Brick:
			newBlock = new BrickBlockObject("");
			break;
		case BlockType::Secret:
			break;
		case BlockType::ItemBrick:
			// newBlock = new BrickBlockObject("");
			break;
		default:
			break;
		}

		if (newBlock == nullptr)
			continue;


		newBlock->LoadBlockSaveData(data);
		newBlock->Start();
		AddGameObject(newBlock, LayerType::Block);
	}

	for (const auto& data : data.itemBlockSaveDatas)
	{
		ItemBlockObject* newBlock = new ItemBlockObject(ItemType::Coin, "", "");
		newBlock->LoadItemBlockSaveData(data);
		newBlock->Start();
		AddGameObject(newBlock, LayerType::Block);
	}

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

	for (const auto& data : data.gameClearSaveDatas)
	{
		GameClearObject* gameClear = new GameClearObject();
		gameClear->LoadGameClearSaveData(data);
		gameClear->Start();
		AddGameObject(gameClear, gameClear->GetLayerType());
	}

	for (const auto& data : data.enemySaveDatas)
	{
		switch ((EnemyType)data.enemyType)
		{
		case EnemyType::Goomba:
		{
			Goomba* enemy = new Goomba();
			enemy->LoadEnemySaveData(data);
			enemy->Start();
			AddGameObject(enemy, enemy->GetLayerType());
		}
		break;
		case EnemyType::KoopaTroopa:
		{
			KoopaTroopa* enemy = new KoopaTroopa();
			enemy->LoadEnemySaveData(data);
			enemy->Start();
			AddGameObject(enemy, enemy->GetLayerType());
		}
		break;
		case EnemyType::Koopa:
		{
			Koopa* enemy = new Koopa();
			enemy->LoadEnemySaveData(data);
			enemy->Start();
			AddGameObject(enemy, enemy->GetLayerType());
		}
		break;
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
