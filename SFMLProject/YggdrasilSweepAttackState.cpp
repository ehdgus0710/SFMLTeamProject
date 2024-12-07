#include "stdafx.h"
#include "YggdrasilSweepAttackState.h"
#include "Rigidbody.h"
#include "Animator.h"
#include "Animation.h"
#include "Collider.h"
#include "GameManager.h"
#include "Yggdrasil.h"
#include "Player.h"
#include "HitBoxObject.h"
#include "YggdrasilLeftHand.h"
#include "YggdrasilRightHand.h"

void YggdrasilSweepAttackState::ReadyAttack(float deltaTime)
{
	currentAttackTime += deltaTime;
	lStartPos = yggdrasil->GetLeftFistPos();
	lEndPos = { yggdrasil->GetPosition().x + 2000.f, 800.f };
	yggdrasil->SetLeftFistPos(sf::Vector2f::Lerp(lStartPos, lEndPos, currentAttackTime / attackDelay));
	rStartPos = yggdrasil->GetRightFistPos();
	rEndPos = { yggdrasil->GetPosition().x - 2000.f, 800.f };
	yggdrasil->SetRightFistPos(sf::Vector2f::Lerp(rStartPos, rEndPos, currentAttackTime / attackDelay));
	isWait = true;
}

void YggdrasilSweepAttackState::StartLeftAttack(float deltaTime)
{
	effectTime += deltaTime;
	if (effectTime > effectDelay)
	{
		CreateLeftEffect();
		effectTime = 0.f;
	}
	currentAttackTime += deltaTime;
	lStartPos = { yggdrasil->GetPosition().x + 2000.f, 800.f };
	lEndPos = { yggdrasil->GetPosition().x - 2000.f, 800.f };
	for (hitBoxOn; hitBoxOn < 1; ++hitBoxOn)
	{
		attackBox1 = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new HitBoxObject(yggdrasil->GetYggdrasilLeftHand(), ColliderLayer::Boss, ColliderLayer::Player, true, (sf::Vector2f::right * 30.f)), LayerType::Boss);
		attackBox1->SetScale({ 400.f,400.f });
		attackBox1->SetDamage(10);
	}
	attackBox1->SetPosition(sf::Vector2f::Lerp(lStartPos, lEndPos, currentAttackTime / attackTime));
	yggdrasil->SetLeftFistPos(sf::Vector2f::Lerp(lStartPos, lEndPos, currentAttackTime / attackTime));

	if (currentAttackTime >= attackTime - 0.5f)
	{
		attackBox1->OnDestory();
	}

	if (currentAttackTime >= readyFistTime)
	{
		hitBoxOn = false;
		switchFist = true;
		++attackCount;
		currentAttackTime = 0.f;
	}
}

void YggdrasilSweepAttackState::StartRightAttack(float deltaTime)
{
	effectTime += deltaTime;
	if (effectTime > effectDelay)
	{
		CreateRightEffect();
		effectTime = 0.f;
	}
	currentAttackTime += deltaTime;
	rStartPos = { yggdrasil->GetPosition().x - 2000.f, 800.f };
	rEndPos = { yggdrasil->GetPosition().x + 2000.f, 800.f };
	for (hitBoxOn; hitBoxOn < 1; ++hitBoxOn)
	{
		attackBox2 = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new HitBoxObject(yggdrasil->GetYggdrasilRightHand(), ColliderLayer::Boss, ColliderLayer::Player, true, (sf::Vector2f::right * 30.f)), LayerType::Boss);
		attackBox2->SetScale({ 400.f,400.f });
		attackBox2->SetDamage(10);
	}
	attackBox2->SetPosition(sf::Vector2f::Lerp(rStartPos, rEndPos, currentAttackTime / attackTime));
	yggdrasil->SetRightFistPos(sf::Vector2f::Lerp(rStartPos, rEndPos, currentAttackTime / attackTime));

	if (currentAttackTime >= attackTime - 0.5f)
	{
		attackBox2->OnDestory();
	}

	if (currentAttackTime >= readyFistTime)
	{
		hitBoxOn = false;
		switchFist = true;
		++attackCount;
		currentAttackTime = 0.f;
	}
}

void YggdrasilSweepAttackState::EndAttackWait(float deltaTime)
{
	currentAttackDelay += deltaTime;

	if (currentAttackDelay >= 0.5f)
	{
		currentAttackDelay = 0.f;
		isRecovery = true;
		isWait = false;
	}
}

void YggdrasilSweepAttackState::Recovery(float deltaTime)
{
	currentAttackTime += deltaTime;
	lStartPos = { yggdrasil->GetPosition().x + 1300.f, 800.f };
	lEndPos = lFirstPos;
	yggdrasil->SetLeftFistPos(sf::Vector2f::Lerp(lStartPos, lEndPos, currentAttackTime / recoveryTime));
	rStartPos = { yggdrasil->GetPosition().x - 1300.f, 800.f };
	rEndPos = rFirstPos;
	yggdrasil->SetRightFistPos(sf::Vector2f::Lerp(rStartPos, rEndPos, currentAttackTime / recoveryTime));
	if (currentAttackTime >= recoveryTime)
	{
		++attackCount;
	}
}

void YggdrasilSweepAttackState::CreateLeftEffect()
{
	AnimationGameObject* effect = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new AnimationGameObject("AttackEffect"), LayerType::Effect);
	Animation* animation(new Animation("animations/Enemy/Yggdrasil/Effects/yggdrasilGrogy.csv"));
	effect->GetAnimator()->AddAnimation(animation, "yggdrasilGrogy");
	effect->GetAnimator()->ChangeAnimation("yggdrasilGrogy");

	animation->SetAnimationEndEvent(std::bind(&GameObject::OnDestory, effect), animation->GetEndFrameCount());
	effect->SetPosition({ yggdrasil->GetLeftFistPos().x, 913.f });
	effect->SetScale(sf::Vector2f::one * 3);

	effect->Awake();
	effect->Start();
}

void YggdrasilSweepAttackState::CreateRightEffect()
{
	AnimationGameObject* effect = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new AnimationGameObject("AttackEffect"), LayerType::Effect);
	Animation* animation(new Animation("animations/Enemy/Yggdrasil/Effects/yggdrasilGrogy.csv"));
	effect->GetAnimator()->AddAnimation(animation, "yggdrasilGrogy");
	effect->GetAnimator()->ChangeAnimation("yggdrasilGrogy");

	animation->SetAnimationEndEvent(std::bind(&GameObject::OnDestory, effect), animation->GetEndFrameCount());
	effect->SetPosition({ yggdrasil->GetRightFistPos().x, 913.f });
	effect->SetScale(sf::Vector2f::one * 3);

	effect->Awake();
	effect->Start();
}

void YggdrasilSweepAttackState::Awake()
{
	YggdrasilBaseState::Awake();
}

void YggdrasilSweepAttackState::Start()
{
	YggdrasilBaseState::Start();
	changeOn = false;
}

void YggdrasilSweepAttackState::Enter()
{
	YggdrasilBaseState::Enter();
	
	if (!yggdrasil->GetPhaseUp())
	{
		yggdrasil->SetAnimeLeftHand("phase1HandLeftSweep", false);
		yggdrasil->SetAnimeRightHand("phase1HandRightSweep", false);

		attackCount = 0;
		whatFist = Utils::RandomRange(1, 2);

		readyAttack = false;
		isAttack = false;
		isRecovery = false;
		isWait = false;
		switchFist = false;
		onAttack = true;

		effectTime = 0.f;
		effectDelay = 0.05f;
		currentAttackDelay = 0.f;
		currentAttackTime = 0.f;
		currentRecoveryTime = 0.f;
		readyFistDelay = 0.f;

		attackDelay = 2.f;
		attackTime = 2.f;
		recoveryTime = 1.f;
		readyFistTime = 2.f;
	}
	else
	{
		yggdrasil->SetAnimeLeftHand("phase2HandLeftSweep", false);
		yggdrasil->SetAnimeRightHand("phase2HandRightSweep", false);

		attackCount = 0;
		whatFist = Utils::RandomRange(1, 2);

		readyAttack = false;
		isAttack = false;
		isRecovery = false;
		isWait = false;
		switchFist = false;
		onAttack = true;

		effectTime = 0.f;
		effectDelay = 0.01f;
		currentAttackDelay = 0.f;
		currentAttackTime = 0.f;
		currentRecoveryTime = 0.f;
		readyFistDelay = 0.f;

		attackDelay = 1.f;
		attackTime = 0.5f;
		recoveryTime = 0.5f;
		readyFistTime = 2.f;
	}
	lFirstPos = yggdrasil->GetLeftFistPos();
	rFirstPos = yggdrasil->GetRightFistPos();

}

void YggdrasilSweepAttackState::Exit()
{
	YggdrasilBaseState::Exit();
}

void YggdrasilSweepAttackState::Update(float deltaTime)
{
	if (yggdrasil->GetPhaseUp() && !changeOn)
	{
		Enter();
		changeOn = true;
	}
	// 휩쓸기 준비 모션
	if (!readyAttack)
	{
		readyFistDelay += deltaTime;
		currentAttackTime = 0.f;
		ReadyAttack(deltaTime);
		if (readyFistDelay > readyFistTime)
		{
			readyAttack = true;
			readyFistDelay = 0.f;
			currentAttackTime = 0.f;
		}
	}
	else
	{
		if (attackCount < 3)
		{
			if (!switchFist)
			{
				if (whatFist == 1)
				{
					StartLeftAttack(deltaTime);
				}
				else if (whatFist == 2)
				{
					StartRightAttack(deltaTime);
				}
			}
			else
			{
				if (whatFist == 1)
				{
					StartRightAttack(deltaTime);
				}
				else if (whatFist == 2)
				{
					StartLeftAttack(deltaTime);
				}
			}
		}
	}
	if (attackCount == 2)
	{
		Recovery(deltaTime);
	}

	if (attackCount == 3)
	{
		fsm->ChangeState(YggdrasilStateType::Idle);
	}


	//if (currentAttackCount == attackCount)
	//	onAttack = false;

	//if (!onAttack)
	//{
	//	fsm->ChangeState(YggdrasilStateType::Idle);
	//}
}

void YggdrasilSweepAttackState::FixedUpdate(float fixedDeltaTime)
{
}

YggdrasilSweepAttackState::YggdrasilSweepAttackState(YggdrasilFSM* fsm)
	: YggdrasilBaseState(fsm, YggdrasilStateType::SweepAttack)
{
}
