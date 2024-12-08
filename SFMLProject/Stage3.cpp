#include "stdafx.h"
#include "Stage3.h"

#include "GameInclude.h"
#include "Animation.h"
#include "ReianaUIHub.h"
#include "PauseUIBar.h"
Stage3::Stage3()
	: Scene(SceneIds::Stage3)
	, pauseUIBar(nullptr)
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
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Wall, ColliderLayer::PlayerHead);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Player, ColliderLayer::Door);

	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Boss, ColliderLayer::PlayerHead);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Reiana, ColliderLayer::PlayerHead);

	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Player, ColliderLayer::EnemyBullet);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Player, ColliderLayer::PlayerHead);

	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::PlayerBullet, ColliderLayer::Reiana);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Player, ColliderLayer::Reiana);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::PlayerHead, ColliderLayer::Reiana);

	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Item, ColliderLayer::Player);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Player, ColliderLayer::Player);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Enemy, ColliderLayer::PlayerBullet);

	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::UI, ColliderLayer::UI);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Wall, ColliderLayer::Player);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Player, ColliderLayer::EnemyBullet);

	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Item, ColliderLayer::Player);

	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Wall, ColliderLayer::PlayerHead);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Reiana, ColliderLayer::PlayerHead);

	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::PlayerBullet, ColliderLayer::Reiana);

	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Wall, ColliderLayer::Reiana);
}

void Stage3::LoadResources()
{

	// Rayanna
	ResourcesManager<sf::Font>::GetInstance().Load("NameFont", "fonts/D2Coding.ttc", true);
	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("Chapter2", "AudioClip/Stage2/Chapter2.wav");
	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("Chapter2_Boss_Awaken", "AudioClip/Stage2/Chapter2_Boss_Awaken.wav");
	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("Leiana_Awakening", "AudioClip/Stage2/Leiana_Awakening.wav");
	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("Leiana_Awakening_Impact", "AudioClip/Stage2/Leiana_Awakening_Impact.wav");
	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("Leiana_Awaken_Dead", "AudioClip/Stage2/Leiana_Awaken_Dead.wav");
	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("Leiana_DarkDimensionRush_Impact", "AudioClip/Stage2/Leiana_DarkDimensionRush_Impact.wav");
	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("Leiana_DarkDimensionRush_Sign", "AudioClip/Stage2/Leiana_DarkDimensionRush_Sign.wav");
	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("Leiana_DarkGoldenMeteor_Ready", "AudioClip/Stage2/Leiana_DarkGoldenMeteor_Ready.wav");
	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("Leiana_DarkMeteor_Impact", "AudioClip/Stage2/Leiana_DarkMeteor_Impact.wav");
	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("Leiana_Dead", "AudioClip/Stage2/Leiana_Dead.wav");
	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("Leiana_MeteorGround", "AudioClip/Stage2/Leiana_MeteorGround.wav");
	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("Leiana_MeteorGround_Ready", "AudioClip/Stage2/Leiana_MeteorGround_Ready.wav");
	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("Leiana_Landing", "AudioClip/Stage2/Leiana_Landing.wav");
	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("Leiana_HomingPierce_Ready", "AudioClip/Stage2/Leiana_HomingPierce_Ready.wav");
	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("Leiana_Teleport_In", "AudioClip/Stage2/Leiana_Teleport_In.wav");
	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("Leiana_Teleport_Out", "AudioClip/Stage2/Leiana_Teleport_Out.wav");
	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("Leiana_FootStep", "AudioClip/Stage2/Leiana_FootStep.wav");
	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("Leiana_DarkHomingPierce", "AudioClip/Stage2/Leiana_DarkHomingPierce.wav");
	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("Leiana_DimensionPierce_Sign", "AudioClip/Stage2/Leiana_DimensionPierce_Sign.wav");
	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("Leiana_DarkDimensionPierce_Sign", "AudioClip/Stage2/Leiana_DarkDimensionPierce_Sign.wav");
	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("Leiana_Awakening_Sign", "AudioClip/Stage2/Leiana_Awakening_Sign.wav");
	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("Leiana_DarkDimensionPierce_Impact", "AudioClip/Stage2/Leiana_DarkDimensionPierce_Impact.wav");
	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("Leiana_HomingPierce_Ready", "AudioClip/Stage2/Leiana_HomingPierce_Ready.wav");
	
	
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

	// Rayanna
	TEXTURE_MANAGER.Load("RayannaB", "graphics/boss/Rayanna/RayannaB.png");
	TEXTURE_MANAGER.Load("AwakenRayanna", "graphics/boss/Rayanna/AwakenRayanna.png");

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
	TEXTURE_MANAGER.Load("DimensionDelete", "graphics/boss/Rayanna/effects/GroundDimension.png");
	TEXTURE_MANAGER.Load("Awake", "graphics/boss/Rayanna/effects/awake.png");
	TEXTURE_MANAGER.Load("DeadCreate", "graphics/boss/Rayanna/effects/deadCreate.png");
	TEXTURE_MANAGER.Load("DeadDelete", "graphics/boss/Rayanna/effects/deadDelete.png");
	TEXTURE_MANAGER.Load("DimensionDelete", "graphics/boss/Rayanna/effects/dimensionDelete.png");
	TEXTURE_MANAGER.Load("DropSide", "graphics/boss/Rayanna/effects/dropSide.png");
	TEXTURE_MANAGER.Load("DropStart", "graphics/boss/Rayanna/effects/dropStart.png");
	TEXTURE_MANAGER.Load("DropEnd", "graphics/boss/Rayanna/effects/dropEnd.png");
	TEXTURE_MANAGER.Load("GroundAttack", "graphics/boss/Rayanna/effects/groundAttack.png");
	TEXTURE_MANAGER.Load("GroundAttackPreparation", "graphics/boss/Rayanna/effects/groundAttackPreparation.png");
	TEXTURE_MANAGER.Load("GroundAttackRazer", "graphics/boss/Rayanna/effects/groundAttackRazer.png");
	TEXTURE_MANAGER.Load("GroundAttackThunder", "graphics/boss/Rayanna/effects/groundAttackThunder.png");
	TEXTURE_MANAGER.Load("Teleport", "graphics/boss/Rayanna/effects/teleport.png");
	TEXTURE_MANAGER.Load("GroundAttackDelay", "graphics/boss/Rayanna/effects/GroundAttackDelay.png");
	TEXTURE_MANAGER.Load("AwakeDimension", "graphics/boss/Rayanna/effects/AwakeDimension.png");

}

void Stage3::Init()
{
	TEXTURE_MANAGER.Load("LittleBone_NonHead", "graphics/skul/LittleBone_NonHead.png");
	TEXTURE_MANAGER.Load("Little Bone", "graphics/skul/Little Bone.png");
	TEXTURE_MANAGER.Load("LittleBoneSkill", "graphics/skul/LittleBoneSkill.png");
	TEXTURE_MANAGER.Load("PlayerHitEffect", "graphics/effects/HitEffect.png");
	TEXTURE_MANAGER.Load("NormalAttack", "graphics/effects/Normal_Attack.png");

	// UI �ɼ�
	TEXTURE_MANAGER.Load("PauseFrame", "graphics/UI/Pause_Frame.png");

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

	TileMap* tileMap = AddGameObject(new TileMap("Stage3TileMap", "Stage3TileMap"), LayerType::TileMap);
	tileMap->LoadCsv("TileMap/Stage3Map1.csv");

	WallCollisionObject* wallObject = AddGameObject(new WallCollisionObject("Wall1"), LayerType::Wall);
	wallObject->SetPosition({ 1182.f, 1372.f });
	wallObject->SetScale({ 3280.f, 960.f });
	wallObject->SetOrigin(Origins::MiddleCenter);

	WallCollisionObject* leftWallObject = AddGameObject(new WallCollisionObject("leftWallObject"), LayerType::Wall);
	leftWallObject->SetPosition({ -48.f, -32.f });
	leftWallObject->SetScale({ 96.f, 2304.f });
	leftWallObject->SetOrigin(Origins::MiddleCenter);

	WallCollisionObject* rightWallObject = AddGameObject(new WallCollisionObject("rightWallObject"), LayerType::Wall);
	rightWallObject->SetPosition({ 2018.f, 384.f });
	rightWallObject->SetScale({ 192.f, 1600.f });
	rightWallObject->SetOrigin(Origins::MiddleCenter);


	Reiana* reiana = AddGameObject(new Reiana("Reiana"), LayerType::Boss);
	reiana->SetPosition({ 1700.f,500.f });

	B_Reiana* b_Reiana = AddGameObject(new B_Reiana("b_Reiana"), LayerType::Boss);
	b_Reiana->SetPosition({ 200.f,500.f });
	
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

	SoundManger::GetInstance().PlayBgm("Chapter2", true);
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

	if (GameManager::GetInstance().IsChangeScene())
	{
		SceneManager::GetInstance().ChangeScene(SceneIds::Stage1);
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