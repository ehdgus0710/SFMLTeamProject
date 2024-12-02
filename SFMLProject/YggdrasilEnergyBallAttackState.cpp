#include "stdafx.h"
#include "YggdrasilEnergyBallAttackState.h"
#include "Rigidbody.h"
#include "Animator.h"
#include "Collider.h"
#include "GameManager.h"
#include "Yggdrasil.h"
#include "Player.h"

void YggdrasilEnergyBallAttackState::EnergyBallFire(sf::Vector2f pos, sf::Vector2f dir, float speed, float deltaTime)
{
	shootTime += deltaTime;
	yggdrasil->SetEnergyBallBigPos(pos + dir * speed * deltaTime);
	for (int i = 0; i < 7; ++i)
	{
		if (i == 0)
		{
			pos = yggdrasil->GetEnergyBallSmallPos(i);
			dir = { 1, -1 };
			yggdrasil->SetEnergyBallSmallPos(pos + dir * speed * deltaTime, i);
		}
		if (i == 1)
		{
			pos = yggdrasil->GetEnergyBallSmallPos(i);
			dir = { 1, 0 };
			yggdrasil->SetEnergyBallSmallPos(pos + dir * speed * deltaTime, i);
		}
		if (i == 2)
		{
			pos = yggdrasil->GetEnergyBallSmallPos(i);
			dir = { 1, 1 };
			yggdrasil->SetEnergyBallSmallPos(pos + dir * speed * deltaTime, i);
		}
		if (i == 3)
		{
			pos = yggdrasil->GetEnergyBallSmallPos(i);
			dir = { 0, 1 };
			yggdrasil->SetEnergyBallSmallPos(pos + dir * speed * deltaTime, i);
		}
		if (i == 4)
		{
			pos = yggdrasil->GetEnergyBallSmallPos(i);
			dir = { -1, 1 };
			yggdrasil->SetEnergyBallSmallPos(pos + dir * speed * deltaTime, i);
		}
		if (i == 5)
		{
			pos = yggdrasil->GetEnergyBallSmallPos(i);
			dir = { -1, 0 };
			yggdrasil->SetEnergyBallSmallPos(pos + dir * speed * deltaTime, i);
		}
		if (i == 6)
		{
			pos = yggdrasil->GetEnergyBallSmallPos(i);
			dir = { -1, -1 };
			yggdrasil->SetEnergyBallSmallPos(pos + dir * speed * deltaTime, i);
		}
		if (i == 7)
		{
			pos = yggdrasil->GetEnergyBallSmallPos(i);
			dir = { 0, -1 };
			yggdrasil->SetEnergyBallSmallPos(pos + dir * speed * deltaTime, i);
		}
	}
	if (shootTime > shootDelay)
	{
		++attackCount;
		isShoot = false;
		shootTime = 0.f;
	}
}

void YggdrasilEnergyBallAttackState::SetEnergySmallBallPos()
{
	for (int i = 0; i < 7; ++i)
	{
		yggdrasil->SetEnergyBallSmallPos(startPos, i);
	}
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
	yggdrasil->SetAnimeEnergyBallBig("EnergyBomb", true);
	yggdrasil->SetAnimeEnergyBallSmall("EnergyBomb", true);


	isShoot = false;

	speed = 1000.f;
	attackCount = 0;
	currentFirstAttack = 0.f;
	firstAttackDelay = 2.f;
	shootTime = 0.f;
	shootDelay = 2.f;

	startPos = { yggdrasil->GetEnergyBallBigPos().x,yggdrasil->GetEnergyBallBigPos().y - 50.f };
}

void YggdrasilEnergyBallAttackState::Exit()
{
	YggdrasilBaseState::Exit();
}

void YggdrasilEnergyBallAttackState::Update(float deltaTime)
{
	//Fire(position, look, bulletspeed, damege);
	if (attackCount < 2)
	{
		if (!isShoot)
		{
			yggdrasil->SetEnergyBallBigPos(startPos);
			SetEnergySmallBallPos();
			currentFirstAttack += deltaTime;
			if (currentFirstAttack > firstAttackDelay)
			{
				//float radi = atan2f(startPos.y - player->GetPosition().y, startPos.x - player->GetPosition().x);
				//float degr = (radi * 180 / Utils::PI) + 90;
				//look = 노멀라이즈 어디있는데 ㅋㅋㅋㅋ;
				look = player->GetPosition() - startPos;
				look.Normalized();
				isShoot = true;
				currentFirstAttack = 0;
			}
		}
		else
		{
			EnergyBallFire(yggdrasil->GetEnergyBallBigPos(), look, speed, deltaTime);
		}
	}
	else
	{
		yggdrasil->SetEnergyBallBigPos(startPos);
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
