#include "stdafx.h"
#include "SceneDev1.h"

#include "GameInclude.h"


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

	GameManager::GetInstance().SetWorldName("1-1");

	StartUIObject* startUIObject = AddGameObject(new StartUIObject(), LayerType::UI);
	InGameUIHub* uiHub = AddGameObject(new InGameUIHub("DungGeunMo", "UIHub"), LayerType::UI);

	backgroundColorBox = AddGameObject(new BackgroundColorBox(), LayerType::Default);
	backgroundColorBox->SetScale({ 2000.f, 1300.f });
	backgroundColorBox->SetColor(sf::Color(85, 151, 248));

	CollisitionCheck();
	
	if (!GameManager::GetInstance().IsRestart())
	{
		Load(loadPath);
		player->ChangeSmallMario();
		GameManager::GetInstance().OnSavePoint(player->GetPosition());
	}
	Scene::Enter();

	GameManager::GetInstance().SetTimerUI(uiHub->GetTextGameObject("TimerUI"));
	GameManager::GetInstance().SetCoinUI(uiHub->GetTextGameObject("CoinUI"));
	GameManager::GetInstance().SetScoreUI(uiHub->GetTextGameObject("ScoreUI"));
	uiHub->GetTextGameObject("WorldUI")->SetString(GameManager::GetInstance().GetWorldName());

	GameManager::GetInstance().GameStartInit();

	// startUIObject->Start();
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
		GameManager::GetInstance().SetMarioHp(player->GetCurrentHP());
		ColliderManager::GetInstance().Clear();
		GameManager::GetInstance().NextStage();
		mainCamera->SetFollowTarget(nullptr);
		return;
	}
	else
	{
		backgroundColorBox->SetPosition(mainCamera->GetCameraPosition());
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

	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Wall, ColliderLayer::Enemy);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Enemy, ColliderLayer::Enemy);

	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Item, ColliderLayer::Player);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Item, ColliderLayer::Wall);

	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Enemy, ColliderLayer::PlayerBullet);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Wall, ColliderLayer::PlayerBullet);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::SavePoint, ColliderLayer::Player);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::CleraPoint, ColliderLayer::Player);
}

void SceneDev1::LoadResources()
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
