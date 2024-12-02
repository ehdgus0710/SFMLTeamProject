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

	sf::Vector2f yggdrasilPos = yggdrasil->GetYggdrasilMouth()->GetPosition();
	Scene* currentScene = SceneManager::GetInstance().GetCurrentScene();
	
	//// 임시
	//{
	//	Animation* animation = new Animation("animations/Enemy/yggdrasil/Effects/EnergyBomb.csv");
	//	yggdrasilEnergyBallSmall[0]->GetAnimator()->AddAnimation(animation, "EnergyBomb");
	//	yggdrasilEnergyBallSmall[0]->GetAnimator()->ChangeAnimation("EnergyBomb", true);

	//	yggdrasilEnergyBallSmall[0]->AddStartHitEvent(std::bind(&YggdrasilEnergyBallAttackState::CreateEffect, this));
	//}
	

	for (int i = 0; i < 7; ++i)
	{
		yggdrasilEnergyBallSmall[i] = currentScene->AddGameObject(new YggdrasilEnergyBallSmall(yggdrasil, ColliderLayer::EnemyBullet, ColliderLayer::Player,"YggdrasilEnergyBallSmall"), LayerType::EnemyBullet);
		yggdrasilEnergyBallSmall[i]->SetPosition({ yggdrasilPos + sf::Vector2f::up * 50.f });
		yggdrasilEnergyBallSmall[i]->SetScale({ 0.5f, 0.5f });
		yggdrasilEnergyBallSmall[i]->Awake();
		yggdrasilEnergyBallSmall[i]->GetCollider()->SetScale({ 50.f,50.f });
		yggdrasilEnergyBallSmall[i]->Start();
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
	yggdrasilEnergyBallBig->SetMoveDirection(look);
	yggdrasilEnergyBallBig->Shoot();
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
}

void YggdrasilEnergyBallAttackState::Awake()
{
	YggdrasilBaseState::Awake();
}

void YggdrasilEnergyBallAttackState::Start()
{
	YggdrasilBaseState::Start();
}

void YggdrasilEnergyBallAttackState::Enter()
{
	YggdrasilBaseState::Enter();
	//yggdrasil->SetAnimeEnergyBallBig("EnergyBomb", true);
	//yggdrasil->SetAnimeEnergyBallSmall("EnergyBomb", true);


	isShoot = false;

	speed = 1000.f;
	attackCount = 0;
	currentFirstAttack = 0.f;
	firstAttackDelay = 2.f;
	shootTime = 0.f;
	shootDelay = 2.f;

	yggdrasilEnergyBallBig = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new YggdrasilEnergyBallBig(yggdrasil, ColliderLayer::EnemyBullet, ColliderLayer::Player, "YggdrasilEnergyBallBig"), LayerType::EnemyBullet);
	yggdrasilEnergyBallBig->SetYggdrasil(yggdrasil);
	yggdrasilEnergyBallBig->SetPosition({ yggdrasil->GetYggdrasilMouth()->GetPosition() + sf::Vector2f::up * 50.f });
	yggdrasilEnergyBallBig->SetScale({ 2.5f, 2.5f });
	yggdrasilEnergyBallBig->SetSpeed(speed);
	yggdrasilEnergyBallBig->Awake();
	yggdrasilEnergyBallBig->GetCollider()->SetScale({ 150.f,150.f });
	yggdrasilEnergyBallBig->Start();

	startPos = yggdrasilEnergyBallBig->GetPosition() + sf::Vector2f::up * 50.f;
}

void YggdrasilEnergyBallAttackState::Exit()
{
	YggdrasilBaseState::Exit();

	yggdrasilEnergyBallBig = nullptr;
}

void YggdrasilEnergyBallAttackState::Update(float deltaTime)
{
	//Fire(position, look, bulletspeed, damege);
	if (attackCount < 2)
	{
		if (!isShoot)
		{
			yggdrasilEnergyBallBig->SetPosition(startPos);
			SetEnergySmallBallPos();
			currentFirstAttack += deltaTime;
			if (currentFirstAttack > firstAttackDelay)
			{
				//float radi = atan2f(startPos.y - player->GetPosition().y, startPos.x - player->GetPosition().x);
				//float degr = (radi * 180 / Utils::PI) + 90;
				//look = 노멀라이즈 어디있는데 ㅋㅋㅋㅋ;
				isShoot = true;
				EnergyBallFire(yggdrasilEnergyBallBig->GetPosition(), look, speed, deltaTime);
				currentFirstAttack = 0;
			}
		}
	}
	else
	{
		yggdrasilEnergyBallBig->SetPosition(startPos);
		SetEnergySmallBallPos();
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
