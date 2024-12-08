#include "stdafx.h"
#include "Stage2.h"

#include "GameInclude.h"
#include "Animation.h"
#include "BackgroundSprite.h"
#include "PlayerUIHub.h"

#include "Yggdrasil.h"
#include "YggdrasilUIHub.h"
#include "SkillCoolTimeUI.h"
#include "PauseUIBar.h"

Stage2::Stage2()
	: Scene(SceneIds::Stage2)
	, player(nullptr)
	, pauseUIBar(nullptr)
	, isChangeScene(false)
{
	savePath = "Stage2.json";
	loadPath = "Stage2.json";


	cameraLimitRect = { -400.f, 2440.f, 0.f, 1080.f };
	currentCameraLimitRect = cameraLimitRect;
}

Stage2::~Stage2()
{
}

void Stage2::CollisitionCheck()
{
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Default, ColliderLayer::Player);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Wall, ColliderLayer::Player);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Enemy, ColliderLayer::Player);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Player, ColliderLayer::EnemyBullet); 
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Player, ColliderLayer::Boss); 
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Wall, ColliderLayer::EnemyBullet);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Player, ColliderLayer::PlayerHead);

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

void Stage2::LoadResources()
{
	ResourcesManager<sf::Font>::GetInstance().Load("Status", "fonts/Perfect DOS VGA 437.ttf", true);
	ResourcesManager<sf::Font>::GetInstance().Load("NameFont2", "fonts/NotoSans-Bold.ttf", true);
	ResourcesManager<sf::Font>::GetInstance().Load("NameFont", "fonts/D2Coding.ttc", true);
	// Yggdrasil
	TEXTURE_MANAGER.Load("YggdrasilBody", "graphics/boss/Yggdrasil/Body.png");
	TEXTURE_MANAGER.Load("YggdrasilHead", "graphics/boss/Yggdrasil/Head.png");
	TEXTURE_MANAGER.Load("YggdrasilMouth", "graphics/boss/Yggdrasil/Mouth.png");
	TEXTURE_MANAGER.Load("YggdrasilRightHand", "graphics/boss/Yggdrasil/Right_Hand.png");
	TEXTURE_MANAGER.Load("YggdrasilLeftHand", "graphics/boss/Yggdrasil/Left_Hand.png");


	// Yggdrasil Background
	TEXTURE_MANAGER.Load("YggdrasilbossBackground1", "graphics/boss/Yggdrasil/backgrounds/bossBackground1.png");
	TEXTURE_MANAGER.Load("YggdrasilbossBackground2", "graphics/boss/Yggdrasil/backgrounds/bossBackground2.png");

	// Yggdrasil Effects
	TEXTURE_MANAGER.Load("YggdrasilGrogy", "graphics/boss/Yggdrasil/effects/Grogy.png");
	TEXTURE_MANAGER.Load("YggdrasilHandSlam", "graphics/boss/Yggdrasil/effects/HandSlam.png");
	TEXTURE_MANAGER.Load("YggdrasilHandSlamBoom", "graphics/boss/Yggdrasil/effects/HandSlam_Boom.png");
	TEXTURE_MANAGER.Load("EnergyBomb", "graphics/boss/Yggdrasil/effects/EnergyBomb.png");
	TEXTURE_MANAGER.Load("ChargingTrail", "graphics/boss/Yggdrasil/effects/P2EnergyCorpsChargingTrail.png");
	TEXTURE_MANAGER.Load("P2EnergyCorpsExplosion", "graphics/boss/Yggdrasil/effects/P2EnergyCorpsExplosion.png");
	TEXTURE_MANAGER.Load("P2EnergyCorpsProjectile", "graphics/boss/Yggdrasil/effects/P2EnergyCorpsProjectile.png");
	TEXTURE_MANAGER.Load("P2EnergyCorpsProjectileEmerge", "graphics/boss/Yggdrasil/effects/P2EnergyCorpsProjectileEmerge.png");
	TEXTURE_MANAGER.Load("P2EnergyCorpsSpark", "graphics/boss/Yggdrasil/effects/P2EnergyCorpsSpark.png");
	TEXTURE_MANAGER.Load("P2EnergyCorpsStartImpact", "graphics/boss/Yggdrasil/effects/P2EnergyCorpsStartImpact.png");

	// map
	TEXTURE_MANAGER.Load("Stage1TileMap", "graphics/TileMap/1_Tile01.png");
	// Player UI
	TEXTURE_MANAGER.Load("PlayerUiFrame", "graphics/UI/PlayerUI/player_ui_frame.png");
	TEXTURE_MANAGER.Load("SkulSimbul", "graphics/UI/PlayerUI/Skul.png");
	TEXTURE_MANAGER.Load("SkullThrow", "graphics/UI/PlayerUI/skull_throw.png");
	TEXTURE_MANAGER.Load("Rebone", "graphics/UI/PlayerUI/rebone.png");
	TEXTURE_MANAGER.Load("PlayerHealthBar", "graphics/UI/PlayerUI/Player_HealthBar.png");

	// Yggdrasil UI
	TEXTURE_MANAGER.Load("BossHealthBarFirstPhase", "graphics/UI/BossUI/BossHealthBar_FirstPhase.png");
	TEXTURE_MANAGER.Load("BossHealthBarSecondPhase", "graphics/UI/BossUI/BossHealthBar_SecondPhase.png");
	TEXTURE_MANAGER.Load("YggdrasilFirstPhaseBottomBack", "graphics/boss/Yggdrasil/UI/Ch1BossFirstPhase_BottomBack.png");
	TEXTURE_MANAGER.Load("YggdrasilFirstPhaseFront", "graphics/boss/Yggdrasil/UI/Ch1BossFirstPhase_Front.png");
	TEXTURE_MANAGER.Load("YggdrasilFirstPhaseTopBack", "graphics/boss/Yggdrasil/UI/Ch1BossFirstPhase_Top_Back.png");
	TEXTURE_MANAGER.Load("YggdrasilSecondPhaseBottomBack", "graphics/boss/Yggdrasil/UI/Ch1BossSecondPhase_Bottom_Back.png");
	TEXTURE_MANAGER.Load("YggdrasilSecondPhaseFront", "graphics/boss/Yggdrasil/UI/Ch1BossSecondPhase_Front.png");
	TEXTURE_MANAGER.Load("YggdrasilSecondPhaseTop", "graphics/boss/Yggdrasil/UI/Ch1BossSecondPhase_Top_Back.png");

}

void Stage2::SetChangeScene(SceneIds id)
{
	if (isChangeScene)
		return;

	changeSceneIds = id;
	isChangeScene = true;
}

void Stage2::Init()
{
	TEXTURE_MANAGER.Load("LittleBone_NonHead", "graphics/skul/LittleBone_NonHead.png");
	TEXTURE_MANAGER.Load("Little Bone", "graphics/skul/Little Bone.png");
	TEXTURE_MANAGER.Load("LittleBoneSkill", "graphics/skul/LittleBoneSkill.png");
	TEXTURE_MANAGER.Load("PlayerHitEffect", "graphics/effects/HitEffect.png");
	TEXTURE_MANAGER.Load("NormalAttack", "graphics/effects/Normal_Attack.png");

	Scene::Init();
}

void Stage2::Enter()
{
	CameraManger::GetInstance().SetCamera(mainCamera);
	CameraManger::GetInstance().SetCamera(uICamera);
	LoadResources();
	CollisitionCheck();

	BackgroundSprite* backgroundObject = AddGameObject(new BackgroundSprite("YggdrasilbossBackground1", "YggdrasilBackground1"), LayerType::BackGround_Back);

	backgroundObject->SetCameraFollow(mainCamera);
	backgroundObject->SetScale({ 3.f, 3.f });
	backgroundObject->SetOrigin(Origins::MiddleCenter);

	/*TileMapController* tilemapController = AddGameObject(new TileMapController("Stage2"), LayerType::TileMap);
	tilemapController->SetSpriteSheetId("Stage1TileMap");
	tilemapController->SetCellSize({ 32.f,32.f });*/

	Yggdrasil* testYggdrasil = AddGameObject(new Yggdrasil("Yggdrasil"), LayerType::Enemy);
	testYggdrasil->Awake();
	testYggdrasil->SetPosition({ 960.f, 400.f });
	testYggdrasil->GetCollider()->SetScale({ 1000.f,1000.f });

	TileMap* tileMap = AddGameObject(new TileMap("Stage1TileMap", "Stage1TileMap"), LayerType::TileMap);
	tileMap->LoadCsv("TileMap/Stage2Map1.csv");

	WallCollisionObject* wallObject = AddGameObject(new WallCollisionObject("Wall1"), LayerType::Wall);
	wallObject->SetPosition({ 1182.f, 1408.f });
	wallObject->SetScale({ 3280.f, 960.f });
	wallObject->SetOrigin(Origins::MiddleCenter);

	WallCollisionObject* leftWall = AddGameObject(new WallCollisionObject("LeftWall"), LayerType::Wall);
	leftWall->SetPosition({ -632.f, 592.f });
	leftWall->SetScale({ 464.f, 1568.f });
	leftWall->SetOrigin(Origins::MiddleCenter);

	WallCollisionObject* rightWall = AddGameObject(new WallCollisionObject("RightWall"), LayerType::Wall);
	rightWall->SetPosition({ 2530.f, 344.f });
	rightWall->SetScale({ 176.f, 1264.f });
	rightWall->SetOrigin(Origins::MiddleCenter);

	Player* testPlayer = AddGameObject(new Player("Player"), LayerType::Player);
	testPlayer->Awake();
	testPlayer->SetPosition({ 960, 500.f });
	testPlayer->GetCollider()->SetScale({ 30.f,30.f });


	mainCamera->SetFollowTarget(testPlayer, true);
	mainCamera->SetCameraLimitRect(currentCameraLimitRect);

	

	pauseUIBar = AddGameObject(new PauseUIBar("PauseFrame", "PauseFrame"), LayerType::UI);
	pauseUIBar->SetScale({ 3.f,3.f });
	pauseUIBar->SetPosition({ mainCamera->GetView().getSize().x * 0.5f, 450.f });
	/*AnimationGameObject* testPlayer = AddGameObject(new AnimationGameObject("Object"), LayerType::Player);
	testPlayer->Awake();
	testPlayer->SetPosition({ 500, 500.f });
	testPlayer->GetAnimator()->LoadCsv("animators/rayanna.csv");
	testPlayer->GetAnimator()->ChangeAnimation("awaken");*/

	Scene::Enter();
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
	
	if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::Escape))
	{
		pauseUIBar->SetActive(!pauseUIBar->IsActive());
	}

	if (GameManager::GetInstance().IsChangeScene())
	{
		SceneManager::GetInstance().ChangeScene(SceneIds::Stage1);
	}

	if (isChangeScene)
	{
		isChangeScene = false;
		SceneManager::GetInstance().ChangeScene(changeSceneIds);
	}
}

void Stage2::Render(sf::RenderWindow& window)
{
	Scene::Render(window);
}

void Stage2::Save(const std::string& savePath)
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

void Stage2::Load(const std::string& loadPath)
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