#include "stdafx.h"
#include "YggdrasilEnergyBallAttackState.h"
#include "Rigidbody.h"
#include "Animator.h"
#include "Collider.h"
#include "GameManager.h"
#include "Yggdrasil.h"
#include "Player.h"

#include "Scene.h"
#include "YggdrasilEnergyBallBig.h"
#include "YggdrasilEnergyBallSmall.h"
#include "YggdrasilMouth.h"
#include "Animation.h"


void YggdrasilEnergyBallAttackState::EnergyBallFire(sf::Vector2f pos, sf::Vector2f dir, float speed, float deltaTime)
{
	if (!yggdrasil->GetPhaseUp())
	{
		sf::Vector2f yggdrasilPos = yggdrasil->GetYggdrasilMouth()->GetPosition();
		Scene* currentScene = SceneManager::GetInstance().GetCurrentScene();

		//// юс╫ц
		//{
		//	Animation* animation = new Animation("animations/Enemy/yggdrasil/Effects/EnergyBomb.csv");
		//	yggdrasilEnergyBallSmall[0]->GetAnimator()->AddAnimation(animation, "EnergyBomb");
		//	yggdrasilEnergyBallSmall[0]->GetAnimator()->ChangeAnimation("EnergyBomb", true);

		//	yggdrasilEnergyBallSmall[0]->AddStartHitEvent(std::bind(&YggdrasilEnergyBallAttackState::CreateEffect, this));
		//}


		for (int i = 0; i < 8; ++i)
		{
			yggdrasilEnergyBallSmall[i] = currentScene->AddGameObject(new YggdrasilEnergyBallSmall(yggdrasil, ColliderLayer::EnemyBullet, ColliderLayer::Player, "YggdrasilEnergyBallSmall"), LayerType::EnemyBullet);
			yggdrasilEnergyBallSmall[i]->SetPosition({ yggdrasilPos + sf::Vector2f::up * 50.f });
			yggdrasilEnergyBallSmall[i]->SetScale({ 0.5f, 0.5f });
			yggdrasilEnergyBallSmall[i]->Awake();
			yggdrasilEnergyBallSmall[i]->GetCollider()->SetScale({ 50.f,50.f });
			yggdrasilEnergyBallSmall[i]->Start();
			yggdrasilEnergyBallSmall[i]->SetDamage(10);
			yggdrasilEnergyBallSmall[i]->Shoot();

			if (i == 0)
			{
				yggdrasilEnergyBallSmall[i]->SetMoveDirection({ 1.f, -1.f });
			}
			else if (i == 1)
			{
				yggdrasilEnergyBallSmall[i]->SetMoveDirection({ 1.f,0.f });
			}
			else if (i == 2)
			{

				yggdrasilEnergyBallSmall[i]->SetMoveDirection({ 1, 1 });
			}
			else if (i == 3)
			{
				yggdrasilEnergyBallSmall[i]->SetMoveDirection({ 0, 1 });
			}
			else if (i == 4)
			{
				yggdrasilEnergyBallSmall[i]->SetMoveDirection({ -1, 1 });
			}
			else if (i == 5)
			{
				yggdrasilEnergyBallSmall[i]->SetMoveDirection({ -1, 0 });
			}
			else if (i == 6)
			{
				yggdrasilEnergyBallSmall[i]->SetMoveDirection({ -1, -1 });
			}
			else if (i == 7)
			{
				yggdrasilEnergyBallSmall[i]->SetMoveDirection({ 0, -1 });
			}
		}

		look = player->GetPosition() - startPos;
		look.Normalized();
		yggdrasilEnergyBallBig[attackCount]->SetMoveDirection(look);
		yggdrasilEnergyBallBig[attackCount]->SetDamage(15);
		yggdrasilEnergyBallBig[attackCount]->Shoot();
		//yggdrasilEnergyBallBig[attackCount]->AddStartHitEvent();
		//if (ball == false)
		//{
		//	CreateEffect();
		//}
	}
	else
	{
		yggdrasilEnergyBallBig[attackCount] = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new YggdrasilEnergyBallBig(yggdrasil, ColliderLayer::EnemyBullet, ColliderLayer::Player, "YggdrasilEnergyBallBig"), LayerType::EnemyBullet);
		yggdrasilEnergyBallBig[attackCount]->SetYggdrasil(yggdrasil);
		yggdrasilEnergyBallBig[attackCount]->SetPosition({ (float)Utils::RandomRange(0, 1920), (float)Utils::RandomRange(100, 200) });
		yggdrasilEnergyBallBig[attackCount]->SetScale({ 2.5f, 2.5f });
		yggdrasilEnergyBallBig[attackCount]->Awake();
		yggdrasilEnergyBallBig[attackCount]->GetCollider()->SetScale({ 80.f,80.f });
		yggdrasilEnergyBallBig[attackCount]->Start();
		yggdrasilEnergyBallBig[attackCount]->SetDamage(15);
		yggdrasilEnergyBallBig[attackCount]->SetPlayer(player);
		yggdrasilEnergyBallBig[attackCount]->SetSpeed(speed);
		yggdrasilEnergyBallBig[attackCount]->SetMoveDirection(sf::Vector2f::down);
		if (shootTime > shootDelay)
		{
			yggdrasilEnergyBallBig[attackCount]->Shoot();
			shootTime = 0.f;
		}

		// look = player->GetPosition() - startPos;
		// look.Normalized();
		// sf::Vector2f pos = yggdrasilEnergyBallBig[attackCount]->GetPosition();
		// yggdrasilEnergyBallBig[attackCount]->SetMoveDirection(look);
		// yggdrasilEnergyBallBig[attackCount]->SetPosition(pos + sf::Vector2f{ 0, 1 } *speed * deltaTime);
	}

}

void YggdrasilEnergyBallAttackState::SetEnergySmallBallPos()
{
	/*for (int i = 0; i < 7; ++i)
	{
		yggdrasilEnergyBallSmall[i]->SetPosition(startPos);
	}*/
}

void YggdrasilEnergyBallAttackState::CreateEffect()
{
	AnimationGameObject* effect = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new AnimationGameObject("AttackEffect"), LayerType::Effect);
	Animation* animation(new Animation("animations/Enemy/Yggdrasil/Effects/P2EnergyCorpsExplosion.csv"));
	effect->GetAnimator()->AddAnimation(animation, "P2EnergyCorpsExplosion");
	effect->GetAnimator()->ChangeAnimation("P2EnergyCorpsExplosion");
	animation->SetAnimationEndEvent(std::bind(&GameObject::OnDestory, effect), animation->GetEndFrameCount());

	effect->SetPosition({ yggdrasilEnergyBallBig[attackCount]->GetPosition().x, 913.f });
	effect->SetScale(sf::Vector2f::one * 3.f);

	effect->Awake();
	effect->Start();
}

void YggdrasilEnergyBallAttackState::Awake()
{
	YggdrasilBaseState::Awake();
}

void YggdrasilEnergyBallAttackState::Start()
{
	YggdrasilBaseState::Start();
	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("ElderEnt_EnergyBomb_Ready", "AudioClip/Stage1/ElderEnt_EnergyBomb_Ready.wav");
	SoundManger::GetInstance().PlaySfx("ElderEnt_EnergyBomb_Ready", false);
	changeOn = false;
	AnimationGameObject* effect = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new AnimationGameObject("AttackEffect"), LayerType::Effect);
}

void YggdrasilEnergyBallAttackState::Enter()
{
	YggdrasilBaseState::Enter();
	//yggdrasil->SetAnimeEnergyBallBig("EnergyBomb", true);
	//yggdrasil->SetAnimeEnergyBallSmall("EnergyBomb", true);

	if (!yggdrasil->GetPhaseUp())
	{
		isShoot = false;

		speed = 1000.f;
		attackCount = 0;
		maxAttackCount = 2;
		currentFirstAttack = 0.f;
		firstAttackDelay = 2.f;
		shootTime = 0.f;
		shootDelay = 0.f;
		for (int i = 0; i < maxAttackCount; ++i)
		{
			yggdrasilEnergyBallBig[i] = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new YggdrasilEnergyBallBig(yggdrasil, ColliderLayer::EnemyBullet, ColliderLayer::Player, "YggdrasilEnergyBallBig"), LayerType::EnemyBullet);
			yggdrasilEnergyBallBig[i]->SetYggdrasil(yggdrasil);
			yggdrasilEnergyBallBig[i]->SetPosition({ yggdrasil->GetYggdrasilMouth()->GetPosition() + sf::Vector2f::up * 50.f });
			yggdrasilEnergyBallBig[i]->SetScale({ 2.5f, 2.5f });
			yggdrasilEnergyBallBig[i]->SetSpeed(speed);
			yggdrasilEnergyBallBig[i]->Awake();
			yggdrasilEnergyBallBig[i]->GetCollider()->SetScale({ 80.f,80.f });
			yggdrasilEnergyBallBig[i]->Start();

		}
		startPos = yggdrasilEnergyBallBig[0]->GetPosition() + sf::Vector2f::up * 50.f;
	}
	else
	{
		isShoot = false;
		speed = 1000.f;
		attackCount = 0;
		maxAttackCount = 10;
		currentFirstAttack = 0.f;
		firstAttackDelay = 0.5f;
		shootTime = 0.f;
		shootDelay = 0.3f;

	}
}

void YggdrasilEnergyBallAttackState::Exit()
{
	YggdrasilBaseState::Exit();
	if (!yggdrasil->GetPhaseUp())
	{
		for (int i = 0; i < maxAttackCount; ++i)
		{
			yggdrasilEnergyBallBig[i] = nullptr;
		}
	}
	else
	{
		for (int i = 0; i < maxAttackCount; ++i)
		{
			yggdrasilEnergyBallBig[i] = nullptr;
		}
	}
}

void YggdrasilEnergyBallAttackState::Update(float deltaTime)
{
	//Fire(position, look, bulletspeed, damege);
	if (yggdrasil->GetPhaseUp() && !changeOn)
	{
		Enter();
		changeOn = true;
	}

	if (attackCount < maxAttackCount)
	{
		if (!isShoot)
		{
			currentFirstAttack += deltaTime;
			if (currentFirstAttack > firstAttackDelay)
			{
				isShoot = true;
				EnergyBallFire(startPos, look, speed, deltaTime);
				currentFirstAttack = 0.f;
				shootTime = 0.f;
				++attackCount;
			}
		}
		shootTime += deltaTime;
		if (shootTime > firstAttackDelay)
		{
			if (attackCount == maxAttackCount - (maxAttackCount - attackCount))
			{
				SoundManger::GetInstance().PlaySfx("ElderEnt_EnergyBomb_Ready", false);
				isShoot = false;
				shootTime = 0.f;
			}
		}
	}
	else
	{
		//SetEnergySmallBallPos();
		fsm->ChangeState(YggdrasilStateType::Idle);
	}
}

void YggdrasilEnergyBallAttackState::FixedUpdate(float fixedDeltaTime)
{
}

YggdrasilEnergyBallAttackState::YggdrasilEnergyBallAttackState(YggdrasilFSM* fsm)
	: YggdrasilBaseState(fsm, YggdrasilStateType::EnergyBallAttack)
{
}
