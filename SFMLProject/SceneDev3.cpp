#include "stdafx.h"
#include "SceneDev3.h"

#include "GameInclude.h"
#include "Animation.h"

void SceneDev3::CollisitionCheck()
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

void SceneDev3::LoadResources()
{
}

void SceneDev3::Init()
{
	TEXTURE_MANAGER.Load("LittleBone_NonHead", "graphics/skul/LittleBone_NonHead.png");
	TEXTURE_MANAGER.Load("Little Bone", "graphics/skul/Little Bone.png");
	TEXTURE_MANAGER.Load("LittleBoneSkill", "graphics/skul/LittleBoneSkill.png");
	TEXTURE_MANAGER.Load("PlayerHitEffect", "graphics/effects/HitEffect.png");
	TEXTURE_MANAGER.Load("NormalAttack", "graphics/effects/Normal_Attack.png");

	Scene::Init();
}

void SceneDev3::Enter()
{
	CameraManger::GetInstance().SetCamera(mainCamera);
	CameraManger::GetInstance().SetCamera(uICamera);

	TEXTURE_MANAGER.Load("YggdrasilBody", "graphics/boss/Yggdrasil/Body.png");
	TEXTURE_MANAGER.Load("YggdrasilHead", "graphics/boss/Yggdrasil/Head.png");
	TEXTURE_MANAGER.Load("YggdrasilMouth", "graphics/boss/Yggdrasil/Mouth.png");
	TEXTURE_MANAGER.Load("YggdrasilRightHand", "graphics/boss/Yggdrasil/Right_Hand.png");
	TEXTURE_MANAGER.Load("YggdrasilLeftHand", "graphics/boss/Yggdrasil/Left_Hand.png");
	TEXTURE_MANAGER.Load("YggdrasilbossBackground1", "graphics/boss/Yggdrasil/backgrounds/bossBackground1.png");
	TEXTURE_MANAGER.Load("YggdrasilbossBackground2", "graphics/boss/Yggdrasil/backgrounds/bossBackground2.png");
	TEXTURE_MANAGER.Load("YggdrasilGrogy", "graphics/boss/Yggdrasil/effects/Grogy.png");
	TEXTURE_MANAGER.Load("YggdrasilHandSlam", "graphics/boss/Yggdrasil/effects/HandSlam.png");
	TEXTURE_MANAGER.Load("YggdrasilHandSlamBoom", "graphics/boss/Yggdrasil/effects/HandSlam_Boom.png");
	TEXTURE_MANAGER.Load("RayannaB", "graphics/boss/Rayanna/RayannaB.png");

	CollisitionCheck();

	AnimationGameObject* testPlayer = AddGameObject(new AnimationGameObject("Object"), LayerType::Player);
	testPlayer->Awake();
	testPlayer->SetPosition({ 500, 500.f });
	testPlayer->GetAnimator()->LoadCsv("animators/rayanna.csv");
	testPlayer->GetAnimator()->ChangeAnimation("awaken");

	Scene::Enter();
}

void SceneDev3::Exit()
{
	Scene::Exit();
}

void SceneDev3::Release()
{
	Scene::Release();
}

void SceneDev3::Update(float dt)
{
	Scene::Update(dt);
}

void SceneDev3::Render(sf::RenderWindow& window)
{
	Scene::Render(window);
}

void SceneDev3::Save(const std::string& savePath)
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

void SceneDev3::Load(const std::string& loadPath)
{
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
}

SceneDev3::SceneDev3()
	: Scene(SceneIds::SceneDev3)
{
	savePath = "SceneDev3.json";
	loadPath = "SceneDev3.json";
}

SceneDev3::~SceneDev3()
{
}
