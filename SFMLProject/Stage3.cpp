#include "stdafx.h"
#include "Stage3.h"

#include "GameInclude.h"
#include "Animation.h"
#include "ReianaUIHub.h"
#include "PauseUIBar.h"
Stage3::Stage3()
	: Scene(SceneIds::Stage3)
{
	savePath = "Stage3.json";
	loadPath = "Stage3.json";

	cameraLimitRect = { 0.f, 1920.f, 0.f, 1080.f };
	currentCameraLimitRect = cameraLimitRect;
}

Stage3::~Stage3()
{
}

void Stage3::CollisitionCheck()
{
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Wall, ColliderLayer::Player);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Wall, ColliderLayer::Enemy);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Wall, ColliderLayer::PlayerBullet);

	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Enemy, ColliderLayer::Player);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Player, ColliderLayer::EnemyBullet);


	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Item, ColliderLayer::Player);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Player, ColliderLayer::Player);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Enemy, ColliderLayer::PlayerBullet);

	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::UI, ColliderLayer::UI);
}

void Stage3::LoadResources()
{

	// Rayanna
	TEXTURE_MANAGER.Load("RayannaB", "graphics/boss/Rayanna/RayannaB.png");
	ResourcesManager<sf::Font>::GetInstance().Load("NameFont", "fonts/D2Coding.ttc", true);

	// Rayanna Effects
	TEXTURE_MANAGER.Load("AwakenedThunder", "graphics/boss/Rayanna/effects/AwakenedThunder.png");
	TEXTURE_MANAGER.Load("DimensionPierce", "graphics/boss/Rayanna/effects/DimensionPierce.png");
	TEXTURE_MANAGER.Load("DimensionPierceAttack", "graphics/boss/Rayanna/effects/DimensionPierceAttack.png");
	TEXTURE_MANAGER.Load("DimensionPierceImpact", "graphics/boss/Rayanna/effects/DimensionPierceImpact.png");
	TEXTURE_MANAGER.Load("goldMeteorLandingSmoke", "graphics/boss/Rayanna/effects/goldMeteorLandingSmoke.png");
	TEXTURE_MANAGER.Load("HomingPierceReady", "graphics/boss/Rayanna/effects/HomingPierceReady.png");
	TEXTURE_MANAGER.Load("IntroLandSmoke", "graphics/boss/Rayanna/effects/IntroLandSmoke.png");
	TEXTURE_MANAGER.Load("MeteorGroundSmoke", "graphics/boss/Rayanna/effects/MeteorGroundSmoke.png");
	TEXTURE_MANAGER.Load("RisingPierce", "graphics/boss/Rayanna/effects/RisingPierce.png");
	TEXTURE_MANAGER.Load("RisingPierceReady", "graphics/boss/Rayanna/effects/RisingPierceReady.png");
	TEXTURE_MANAGER.Load("TwinMeteor", "graphics/boss/Rayanna/effects/TwinMeteor.png");
	TEXTURE_MANAGER.Load("TwinMeteorSign", "graphics/boss/Rayanna/effects/TwinMeteorSign.png");

	TEXTURE_MANAGER.Load("Stage3TileMap", "graphics/TileMap/3_Tile03.png");
	TEXTURE_MANAGER.Load("Background1", "graphics/boss/Rayanna/backgrounds/Background1.png");
	TEXTURE_MANAGER.Load("Background2", "graphics/boss/Rayanna/backgrounds/Background2.png");


	TEXTURE_MANAGER.Load("BossHealthBarFirstPhase", "graphics/UI/BossUI/BossHealthBar_FirstPhase.png");
	TEXTURE_MANAGER.Load("BossHealthBarSecondPhase", "graphics/UI/BossUI/BossHealthBar_SecondPhase.png");

	TEXTURE_MANAGER.Load("Ch2BossFirstPhaseTopBack", "graphics/boss/Rayanna/UI/Ch2BossFirstPhase_Top_Back.png");
	TEXTURE_MANAGER.Load("Ch2BossFirstPhaseFront", "graphics/boss/Rayanna/UI/Ch2BossFirstPhase_Front.png");
	TEXTURE_MANAGER.Load("Ch2BossFirstPhaseBottomBack", "graphics/boss/Rayanna/UI/Ch2BossFirstPhase_Bottom_Back.png");
	TEXTURE_MANAGER.Load("Ch2BossSecondPhaseTopBack", "graphics/boss/Rayanna/UI/Ch2BossSecondPhase_Top_Back.png");
	TEXTURE_MANAGER.Load("Ch2BossSecondPhaseFront",		"graphics/boss/Rayanna/UI/Ch2BossSecondPhase_Front.png");
	TEXTURE_MANAGER.Load("Ch2BossSecondPhaseBottomBack", "graphics/boss/Rayanna/UI/Ch2BossSecondPhase_Bottom_Back.png");

	TEXTURE_MANAGER.Load("PauseFrame", "graphics/UI/Pause_Frame.png");
}

void Stage3::Init()
{
	TEXTURE_MANAGER.Load("LittleBone_NonHead", "graphics/skul/LittleBone_NonHead.png");
	TEXTURE_MANAGER.Load("Little Bone", "graphics/skul/Little Bone.png");
	TEXTURE_MANAGER.Load("LittleBoneSkill", "graphics/skul/LittleBoneSkill.png");
	TEXTURE_MANAGER.Load("PlayerHitEffect", "graphics/effects/HitEffect.png");
	TEXTURE_MANAGER.Load("NormalAttack", "graphics/effects/Normal_Attack.png");

	Scene::Init();
}

void Stage3::Enter()
{
	CameraManger::GetInstance().SetCamera(mainCamera);
	CameraManger::GetInstance().SetCamera(uICamera);

	mainCamera->SetCameraLimitRect(currentCameraLimitRect);

	LoadResources();
	CollisitionCheck();

	SpriteGameObject* backgroundObject = AddGameObject(new SpriteGameObject("Background1", "Background1"), LayerType::BackGround_Back);

	backgroundObject->SetPosition({ 960.f, 500.f});
	backgroundObject->SetScale({ 2.5f, 2.5f });
	backgroundObject->SetOrigin(Origins::MiddleCenter);

	SpriteGameObject* backgroundObject1 = AddGameObject(new SpriteGameObject("Background2", "Background2"), LayerType::BackGround_Back);

	backgroundObject1->SetPosition({ 960.f, 500.f });
	backgroundObject1->SetScale({ 2.5f, 2.5f });
	backgroundObject1->SetOrigin(Origins::MiddleCenter);

	/*TileMapController* tilemapController = AddGameObject(new TileMapController("Stage3"), LayerType::TileMap);
	tilemapController->SetSpriteSheetId("Stage3TileMap");
	tilemapController->SetCellSize({ 32.f,32.f });*/

	TileMap* tileMap = AddGameObject(new TileMap("Stage3TileMap", "Stage3TileMap"), LayerType::TileMap);
	tileMap->LoadCsv("TileMap/Stage3Map1.csv");

	WallCollisionObject* wallObject = AddGameObject(new WallCollisionObject("Wall1"), LayerType::Wall);
	wallObject->SetPosition({ 1182.f, 1372.f });
	wallObject->SetScale({ 3280.f, 960.f });
	wallObject->SetOrigin(Origins::MiddleCenter);
	

	Player* testPlayer = AddGameObject(new Player("Player"), LayerType::Player);
	testPlayer->Awake();
	testPlayer->SetPosition({ 0, -500.f });
	testPlayer->GetCollider()->SetScale({ 30.f,30.f });

	
	ReianaUIHub* reianaUIHub = AddGameObject(new ReianaUIHub("ReianaUIHub"), LayerType::InGameUI);

	pauseUIBar = AddGameObject(new PauseUIBar("PauseFrame","PauseFrame"), LayerType::UI);
	pauseUIBar->SetScale({ 3.f,3.f });
	pauseUIBar->SetPosition({ mainCamera->GetView().getSize().x * 0.5f, 450.f });
	/*AnimationGameObject* testPlayer = AddGameObject(new AnimationGameObject("Object"), LayerType::Player);
	testPlayer->Awake();
	testPlayer->SetPosition({ 500, 500.f });
	testPlayer->GetAnimator()->LoadCsv("animators/rayanna.csv");
	testPlayer->GetAnimator()->ChangeAnimation("awaken");*/

	InputManager::GetInstance().BindKey(sf::Keyboard::Escape);

	Scene::Enter();
}

void Stage3::Exit()
{
	Scene::Exit();
}

void Stage3::Release()
{
	Scene::Release();
}

void Stage3::Update(float dt)
{
	Scene::Update(dt);

	if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::Escape))
	{
		pauseUIBar->SetActive(!pauseUIBar->IsActive());
	}
}

void Stage3::Render(sf::RenderWindow& window)
{
	Scene::Render(window);
}

void Stage3::Save(const std::string& savePath)
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

void Stage3::Load(const std::string& loadPath)
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