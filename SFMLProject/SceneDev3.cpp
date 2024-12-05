#include "stdafx.h"
#include "SceneDev3.h"

#include "GameInclude.h"
#include "Animation.h"
#include "SkillCoolTimeUI.h"

void SceneDev3::CollisitionCheck()
{
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Default, ColliderLayer::Player);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Wall, ColliderLayer::Player);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Enemy, ColliderLayer::Player);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Player, ColliderLayer::EnemyBullet);

	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Wall, ColliderLayer::Enemy);
	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Enemy, ColliderLayer::Enemy);

	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Item, ColliderLayer::Player);

	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Player, ColliderLayer::Player);
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
	TEXTURE_MANAGER.Load("HitEffect", "graphics/effects/HitEffect.png");

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


	TEXTURE_MANAGER.Load("EnergyBomb", "graphics/boss/Yggdrasil/effects/EnergyBomb.png");
	TEXTURE_MANAGER.Load("ChargingTrail", "graphics/boss/Yggdrasil/effects/P2EnergyCorpsChargingTrail.png");
	TEXTURE_MANAGER.Load("P2EnergyCorpsExplosion", "graphics/boss/Yggdrasil/effects/P2EnergyCorpsExplosion.png");
	TEXTURE_MANAGER.Load("P2EnergyCorpsProjectile", "graphics/boss/Yggdrasil/effects/P2EnergyCorpsProjectile.png");
	TEXTURE_MANAGER.Load("P2EnergyCorpsProjectileEmerge", "graphics/boss/Yggdrasil/effects/P2EnergyCorpsProjectileEmerge.png");
	TEXTURE_MANAGER.Load("P2EnergyCorpsSpark", "graphics/boss/Yggdrasil/effects/P2EnergyCorpsSpark.png");
	TEXTURE_MANAGER.Load("P2EnergyCorpsStartImpact", "graphics/boss/Yggdrasil/effects/P2EnergyCorpsStartImpact.png");


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

	TEXTURE_MANAGER.Load("AwakenRayanna", "graphics/boss/Rayanna/AwakenRayanna.png");

	// Player UI
	TEXTURE_MANAGER.Load("PlayerUiFrame", "graphics/UI/PlayerUI/player_ui_frame.png");
	TEXTURE_MANAGER.Load("SkulSimbul", "graphics/UI/PlayerUI/Skul.png");
	TEXTURE_MANAGER.Load("SkullThrow", "graphics/UI/PlayerUI/skull_throw.png");
	TEXTURE_MANAGER.Load("Rebone", "graphics/UI/PlayerUI/rebone.png");
	TEXTURE_MANAGER.Load("PlayerHealthBar", "graphics/UI/PlayerUI/Player_HealthBar.png");

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


	AnimationGameObject* effect1 = AddGameObject(new AnimationGameObject("AwakenedThunder"), LayerType::Player);
	effect1->Awake();


	sf::Vector2f currentPos = { 500, 500.f };
	sf::Vector2f addPos = { 50, 50.f };

	effect1->SetPosition(currentPos);

	Animation* animation = new Animation("animations/Enemy/Rayanna/Effects/AwakenedThunder.csv");
	effect1->GetAnimator()->AddAnimation(animation, "AwakenedThunder");

	animation = new Animation("animations/Enemy/Rayanna/Effects/DimensionPierce.csv");
	effect1->GetAnimator()->AddAnimation(animation, "DimensionPierce");

	animation = new Animation("animations/Enemy/Rayanna/Effects/DimensionPierceAttack.csv");
	effect1->GetAnimator()->AddAnimation(animation, "DimensionPierceAttack");

	animation = new Animation("animations/Enemy/Rayanna/Effects/DimensionPierceImpact.csv");
	effect1->GetAnimator()->AddAnimation(animation, "DimensionPierceImpact");

	animation = new Animation("animations/Enemy/Rayanna/Effects/goldMeteorLandingSmoke.csv");
	effect1->GetAnimator()->AddAnimation(animation, "goldMeteorLandingSmoke");

	animation = new Animation("animations/Enemy/Rayanna/Effects/HomingPierceReady.csv");
	effect1->GetAnimator()->AddAnimation(animation, "HomingPierceReady");

	animation = new Animation("animations/Enemy/Rayanna/Effects/IntroLandSmoke.csv");
	effect1->GetAnimator()->AddAnimation(animation, "IntroLandSmoke");

	animation = new Animation("animations/Enemy/Rayanna/Effects/MeteorGroundSmoke.csv");
	effect1->GetAnimator()->AddAnimation(animation, "MeteorGroundSmoke");

	animation = new Animation("animations/Enemy/Rayanna/Effects/RisingPierce.csv");
	effect1->GetAnimator()->AddAnimation(animation, "RisingPierce");

	animation = new Animation("animations/Enemy/Rayanna/Effects/RisingPierceReady.csv");
	effect1->GetAnimator()->AddAnimation(animation, "RisingPierceReady");

	animation = new Animation("animations/Enemy/Rayanna/Effects/TwinMeteor.csv");
	effect1->GetAnimator()->AddAnimation(animation, "TwinMeteor");

	animation = new Animation("animations/Enemy/Rayanna/Effects/TwinMeteorSign.csv");
	effect1->GetAnimator()->AddAnimation(animation, "TwinMeteorSign");

	effect1->GetAnimator()->ChangeAnimation("AwakenedThunder", true);
	currentPos += addPos;


	CollisitionCheck();

	SkillCoolTimeUI* coolTimeUI = AddGameObject(new SkillCoolTimeUI("SkulSimbul", "Skill1"), LayerType::InGameUI);
	coolTimeUI->SetPosition({ 300.f,300.f });
	coolTimeUI->SetScale({ 2.5f,2.5f });
	//AnimationGameObject* testPlayer = AddGameObject(new AnimationGameObject("Object"), LayerType::Player);
	//testPlayer->Awake();
	//testPlayer->SetPosition({ 500, 500.f });
	//testPlayer->GetAnimator()->LoadCsv("animators/rayanna.csv");
	//testPlayer->GetAnimator()->ChangeAnimation("awaken");

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
