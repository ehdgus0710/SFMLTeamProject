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
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Player, ColliderLayer::Player);

	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Wall, ColliderLayer::Reiana);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::PlayerBullet, ColliderLayer::Reiana);

	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Wall, ColliderLayer::Reiana);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::PlayerBullet, ColliderLayer::Reiana);

	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Enemy, ColliderLayer::PlayerBullet);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Wall, ColliderLayer::PlayerBullet);

	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::SavePoint, ColliderLayer::Player);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::CleraPoint, ColliderLayer::Player);
}

void SceneDev2::LoadResources()
{
	// ½ºÄÃ 
	TEXTURE_MANAGER.Load("LittleBone_NonHead", "graphics/skul/LittleBone_NonHead.png");
	TEXTURE_MANAGER.Load("Little Bone", "graphics/skul/Little Bone.png");
	TEXTURE_MANAGER.Load("LittleBoneSkill", "graphics/skul/LittleBoneSkill.png");
	TEXTURE_MANAGER.Load("PlayerHitEffect", "graphics/effects/HitEffect.png");
	TEXTURE_MANAGER.Load("NormalAttack", "graphics/effects/Normal_Attack.png");

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
}

void SceneDev2::TestEffect()
{
	AnimationGameObject* effect1 = AddGameObject(new AnimationGameObject("AwakenedThunder"), LayerType::Player);
	effect1->Awake();


	sf::Vector2f currentPos = { 500, 500.f };
	sf::Vector2f addPos = { 50, 50.f };

	effect1->SetPosition(currentPos);

	Animation* animation = new Animation();
	animation->loadFromFile("animations/Enemy/Rayanna/Effects/AwakenedThunder.csv");
	effect1->GetAnimator()->AddAnimation(animation, "AwakenedThunder");
	animation = new Animation();

	animation->loadFromFile("animations/Enemy/Rayanna/Effects/DimensionPierce.csv");
	effect1->GetAnimator()->AddAnimation(animation, "DimensionPierce");
	animation = new Animation();

	animation->loadFromFile("animations/Enemy/Rayanna/Effects/DimensionPierceAttack.csv");
	effect1->GetAnimator()->AddAnimation(animation, "DimensionPierceAttack");
	animation = new Animation();

	animation->loadFromFile("animations/Enemy/Rayanna/Effects/DimensionPierceImpact.csv");
	effect1->GetAnimator()->AddAnimation(animation, "DimensionPierceImpact");
	animation = new Animation();

	animation->loadFromFile("animations/Enemy/Rayanna/Effects/goldMeteorLandingSmoke.csv");
	effect1->GetAnimator()->AddAnimation(animation, "goldMeteorLandingSmoke");

	animation = new Animation();
	animation->loadFromFile("animations/Enemy/Rayanna/Effects/HomingPierceReady.csv");
	effect1->GetAnimator()->AddAnimation(animation, "HomingPierceReady");

	animation = new Animation();
	animation->loadFromFile("animations/Enemy/Rayanna/Effects/IntroLandSmoke.csv");
	effect1->GetAnimator()->AddAnimation(animation, "IntroLandSmoke");

	animation = new Animation();
	animation->loadFromFile("animations/Enemy/Rayanna/Effects/MeteorGroundSmoke.csv");
	effect1->GetAnimator()->AddAnimation(animation, "MeteorGroundSmoke");

	animation = new Animation();
	animation->loadFromFile("animations/Enemy/Rayanna/Effects/RisingPierce.csv");
	effect1->GetAnimator()->AddAnimation(animation, "RisingPierce");

	animation = new Animation();
	animation->loadFromFile("animations/Enemy/Rayanna/Effects/RisingPierceReady.csv");
	effect1->GetAnimator()->AddAnimation(animation, "RisingPierceReady");

	animation = new Animation();
	animation->loadFromFile("animations/Enemy/Rayanna/Effects/TwinMeteor.csv");
	effect1->GetAnimator()->AddAnimation(animation, "TwinMeteor");

	animation = new Animation();
	animation->loadFromFile("animations/Enemy/Rayanna/Effects/TwinMeteorSign.csv");
	effect1->GetAnimator()->AddAnimation(animation, "TwinMeteorSign");

	effect1->GetAnimator()->ChangeAnimation("AwakenedThunder", true);
	currentPos += addPos;

}

void SceneDev2::Init()
{
	cameraLimitRect = { 0.f, 1920.f, -880.f, 200.f };
	currentCameraLimitRect = cameraLimitRect;

	Scene::Init();
}

void SceneDev2::Enter()
{
	CameraManger::GetInstance().SetCamera(mainCamera);
	CameraManger::GetInstance().SetCamera(uICamera);
	LoadResources();
	CollisitionCheck();


	Player* testPlayer = AddGameObject(new Player("Player"), LayerType::Player);
	testPlayer->Awake();
	mainCamera->SetFollowTarget(testPlayer, true);
	mainCamera->SetCameraLimitRect(currentCameraLimitRect);
	testPlayer->SetPosition({ 0, -500.f });
	testPlayer->GetCollider()->SetScale({ 100.f,100.f });

	Reiana* testReiana = AddGameObject(new Reiana("Reiana"), LayerType::Boss);
	testReiana->Awake();
	testReiana->SetPosition({ 1700.f,-500.f });

	B_Reiana* testBReiana = AddGameObject(new B_Reiana("Reiana"), LayerType::Boss);
	testBReiana->Awake();
	testBReiana->SetPosition({ 200.f,-500.f });

	AwakeReiana* testAwakeReiana = AddGameObject(new AwakeReiana("AwakeReiana"), LayerType::Boss);
	testAwakeReiana->Awake();
	testAwakeReiana->SetPosition({ 800.f,-500.f });

	WallCollisionObject* wallCollision = AddGameObject(new WallCollisionObject, LayerType::Wall);
	wallCollision->SetScale({ 10000.f, 30.f });
	wallCollision->SetPosition({ 0, 100.f });

	BackgroundColorBox* background = AddGameObject(new BackgroundColorBox(), LayerType::Default);
	background->SetScale({ 2000.f, 1300.f });
	background->SetColor(sf::Color(85, 151, 248));

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
