#include "stdafx.h"
#include "Stage2.h"

#include "GameInclude.h"

void Stage2::CollisitionCheck()
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

void Stage2::LoadResources()
{
	TEXTURE_MANAGER.Load("Player", "graphics/player.png");
	TEXTURE_MANAGER.Load("enemies", "graphics/enemies.png");
	TEXTURE_MANAGER.Load("Items", "graphics/item_objects.png");
	TEXTURE_MANAGER.Load("tiles", "graphics/tiles.png");
	TEXTURE_MANAGER.Load("tile_set", "graphics/tile_set.png");
	TEXTURE_MANAGER.Load("mario_bros", "graphics/mario_bros.png");
	TEXTURE_MANAGER.Load("font", "graphics/font.png");
	ResourcesManager<sf::Font>::GetInstance().Load("DungGeunMo", "fonts/DungGeunMo.ttf", true);

	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("BigJump", "sound/big_jump.ogg");
	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("SmallJump", "sound/small_jump.ogg");
	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("Stomp", "sound/stomp.ogg");
	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("Fireball", "sound/fireball.ogg");
	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("BrickSmash", "sound/brick_smash.ogg");
	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("Chop", "sound/chop.wav");

	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("PowerUpAppears", "sound/powerup_appears.ogg");
	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("PowerUp", "sound/powerup.ogg");
	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("Kick", "sound/kick.ogg");
	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("Coin", "sound/coin.ogg");

	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("OneUp", "sound/one_up.ogg");
	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("Coin", "sound/coin.ogg");
	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("Bump", "sound/bump.ogg");

	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("OutOfTime", "sound/out_of_time.wav");


	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("CountDown", "sound/count_down.ogg");
	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("Flagpole", "sound/bgm/flagpole.wav");
	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("MainTheme", "sound/bgm/main_theme.ogg");

	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("DeathBGM", "sound/bgm/death.wav");
	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("GameOver", "sound/bgm/game_over.ogg");
	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("Invincible", "sound/bgm/invincible.ogg");

	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("StageClear", "sound/bgm/stage_clear.wav");
	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("WorldClear", "sound/bgm/world_clear.wav");

}

void Stage2::Init()
{
	cameraLimitRect = { 0.f,5500.f,-500.f, 700.f };
	currentCameraLimitRect = cameraLimitRect;

	Scene::Init();
}

void Stage2::Enter()
{
	CameraManger::GetInstance().SetCamera(mainCamera);
	CameraManger::GetInstance().SetCamera(uICamera);

	LoadResources();

	GameManager::GetInstance().SetWorldName("1-4");
	// Player* testPlayer = AddGameObject(new Player("Player"), LayerType::Player);
	// testPlayer->Awake();
	// mainCamera->SetFollowTarget(testPlayer, true);

	// Koopa* koopa = AddGameObject(new Koopa(), LayerType::Enemy);
	// koopa->Awake();
	// koopa->SetPosition({ 3500.f, 310.f });

	// TimeManager::GetInstance().SetTimeScale(0.f);
	// TileMapController* tileMapController = AddGameObject(new TileMapController("TileMapController"), LayerType::Default);
	StartUIObject* startUIObject = AddGameObject(new StartUIObject(), LayerType::UI);

	InGameUIHub* uiHub = AddGameObject(new InGameUIHub("DungGeunMo", "UIHub"), LayerType::UI);

	BackgroundColorBox* background = AddGameObject(new BackgroundColorBox(), LayerType::Default);
	background->SetScale({ 2000.f, 1300.f });
	background->SetColor(sf::Color::Black);

	LabberObject* laberObject = AddGameObject(new LabberObject({ 0, 8 * 16,16,16 }, "Items", "labber"), LayerType::Default);
	laberObject->SetPosition({ 3746.f, 350.f });

	TriggerObject* triggerObject = AddGameObject(new TriggerObject(), LayerType::Default);
	triggerObject->SetPosition({ 4546.f, 350.f });
	triggerObject->SetScale({ 10.f, 5000.f });


	CollisitionCheck();

	//TimeManager::GetInstance().SetTimeScale(0.f);

	if (GameManager::GetInstance().IsRestart())
	{
		// GameManager::GetInstance().OnSavePoint();

	}
	else
	{
		Load(loadPath);
		GameManager::GetInstance().OnSavePoint(player->GetPosition());
		player->SetHp(GameManager::GetInstance().GetMarioHp());
		// SaveLoadManager::GetInstance().Load();
		//GameManager::GetInstance().OnSavePoint();
	}

	Scene::Enter();
	GameManager::GetInstance().SetTimerUI(uiHub->GetTextGameObject("TimerUI"));
	GameManager::GetInstance().SetCoinUI(uiHub->GetTextGameObject("CoinUI"));
	GameManager::GetInstance().SetScoreUI(uiHub->GetTextGameObject("ScoreUI"));
	uiHub->GetTextGameObject("WorldUI")->SetString("1-4");

	GameManager::GetInstance().GameStartInit();


	EndingCreditTimeLine* creadit = AddGameObject(new EndingCreditTimeLine("DungGeunMo", "Ending", 100), LayerType::UI);

	creadit->SetPosition({ 960.f, 400.f });
	creadit->SetOrigin(Origins::MiddleCenter);
	creadit->SetString("THANK  YOU  MARIO!");

	triggerObject->AddEnterEvenet(std::bind(&EndingCreditTimeLine::OnStartCreadit, creadit));
	creadit->Start();
}

void Stage2::Exit()
{
	Scene::Exit();
}

void Stage2::Release()
{
	Scene::Release();
}

void Stage2::Update(float dt)
{
	Scene::Update(dt);

	if (GameManager::GetInstance().IsRestart())
	{
		ColliderManager::GetInstance().Clear();
		GameManager::GetInstance().ReStart();
		
		if (GameManager::GetInstance().IsGameOver())
		{
			mainCamera->SetFollowTarget(nullptr);
			player = nullptr;
			return;
		}

		player = (Player*)GetObjectVector(LayerType::Player)[0];
	}
	else if (GameManager::GetInstance().IsEndAdjustment())
	{
		ColliderManager::GetInstance().Clear();
		GameManager::GetInstance().NextStage();
		return;
	}
	else
	{
		GameManager::GetInstance().Update(dt);
	}

	if (player != nullptr)
	{
		if (currentCameraLimitRect.leftPosition < player->GetPosition().x - 800.f)
		{
			currentCameraLimitRect.leftPosition = player->GetPosition().x - 800.f;
			mainCamera->SetCameraLimitRect(currentCameraLimitRect);
		}

	}
}

void Stage2::Render(sf::RenderWindow& window)
{
	Scene::Render(window);
}

void Stage2::Save(const std::string& savePath)
{
	SaveDataVC data;

	data.playerData = ((Player*)FindGameObject("Player"))->GetPlayerSaveData();

	currentCameraLimitRect = cameraLimitRect;
	if (currentCameraLimitRect.leftPosition < player->GetPosition().x - 800.f)
	{
		currentCameraLimitRect.leftPosition = player->GetPosition().x - 800.f;
		mainCamera->SetCameraLimitRect(currentCameraLimitRect);
	}

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
			if (gameClearObject != nullptr)
			{
				data.gameClearSaveDatas.push_back(gameClearObject->GetGameClearSaveData());
				continue;
			}

			auto enemy = dynamic_cast<Enemy*>(gameObject);
			if (enemy != nullptr)
			{
				data.enemySaveDatas.push_back(enemy->GetEnemySaveData());
				continue;
			}
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

void Stage2::Load(const std::string& loadPath)
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
		AddGameObject(newBlock, newBlock->GetLayerType());
	}

	for (const auto& data : data.itemBlockSaveDatas)
	{
		ItemBlockObject* newBlock = new ItemBlockObject(ItemType::Coin, "", "");
		newBlock->LoadItemBlockSaveData(data);
		newBlock->Start();
		AddGameObject(newBlock, newBlock->GetLayerType());
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

Stage2::Stage2()
	: Scene(SceneIds::Stage2)
	, player(nullptr)
{
	savePath = "stage2.json";
	loadPath = "stage2.json";
}

Stage2::~Stage2()
{
}
