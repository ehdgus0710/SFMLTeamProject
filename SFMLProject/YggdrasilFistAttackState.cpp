#include "stdafx.h"
#include "YggdrasilFistAttackState.h"
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

void YggdrasilFistAttackState::ReadyFist(float deltaTime)
{
	currentAttackTime += deltaTime;
	startPos = yggdrasil->GetLeftFistPos();
	endPos = { yggdrasil->GetLeftFistPos().x, yggdrasil->GetPosition().y - 200 };
	yggdrasil->SetLeftFistPos(sf::Vector2f::Lerp(startPos, endPos, currentAttackTime / readyDelay));
	startPos = yggdrasil->GetRightFistPos();
	endPos = { yggdrasil->GetRightFistPos().x, yggdrasil->GetPosition().y - 200 };
	yggdrasil->SetRightFistPos(sf::Vector2f::Lerp(startPos, endPos, currentAttackTime / readyDelay));



	if (currentAttackTime > readyDelay * 2.f)
	{
		//startPos = endPos;
		//endPos = { player->GetPosition().x, 0.f };
		currentAttackTime = 0.f;
	}

}

void YggdrasilFistAttackState::StartAttack(float deltaTime)
{

	switchFistDelay = 0.f;
	if (!switchFist)
	{
		for (hitBoxOn; hitBoxOn < 1; ++hitBoxOn)
		{
			attackBox = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new HitBoxObject(yggdrasil->GetYggdrasilLeftHand(), ColliderLayer::Boss, ColliderLayer::Player, true, (sf::Vector2f::right * 30.f)), LayerType::Boss);
			attackBox->SetScale({ 400.f,400.f });
			attackBox->SetDamage(10);
		}
		attackBox->SetPosition(sf::Vector2f::Lerp(startPos, endPos, currentAttackTime / attackTime));
		currentAttackTime += deltaTime;
		yggdrasil->SetLeftFistPos(sf::Vector2f::Lerp(startPos, endPos, currentAttackTime / attackTime));

		if (currentAttackTime >= attackTime)
		{
			SoundManger::GetInstance().PlaySfx("ElderEnt_FistSlam", false);
			SoundManger::GetInstance().SetSfxVolume(100.f);
			CreateLeftEffect();
			attackBox->OnDestory();
			hitBoxOn = false;
			currentAttackTime = 0.f;
			currentAttackDelay = 0.f;
			isWait = true;
		}
	}
	else
	{
		for (hitBoxOn; hitBoxOn < 1; ++hitBoxOn)
		{
			attackBox = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new HitBoxObject(yggdrasil->GetYggdrasilRightHand(), ColliderLayer::Boss, ColliderLayer::Player, true, (sf::Vector2f::right * 30.f)), LayerType::Boss);
			attackBox->SetScale({ 400.f,400.f });
			attackBox->SetDamage(10);
		}
		attackBox->SetPosition(sf::Vector2f::Lerp({ startPos.x - 100.f,startPos.y }, endPos, currentAttackTime / attackTime));
		currentAttackTime += deltaTime;
		yggdrasil->SetRightFistPos(sf::Vector2f::Lerp(startPos, endPos, currentAttackTime / attackTime));



		if (currentAttackTime >= attackTime)
		{
			SoundManger::GetInstance().PlaySfx("ElderEnt_FistSlam", false);
			SoundManger::GetInstance().SetSfxVolume(100.f);
			CreateRightEffect();
			attackBox->OnDestory();
			hitBoxOn = false;
			currentAttackTime = 0.f;
			currentAttackDelay = 0.f;
			isWait = true;
		}
	}
}

void YggdrasilFistAttackState::EndAttackWait(float deltaTime)
{
	currentAttackDelay += deltaTime;


	if (currentAttackDelay >= waitTime)
	{
		currentAttackDelay = 0.f;
		isRecovery = true;
		isWait = false;
	}
}

void YggdrasilFistAttackState::EndFistPos(float deltaTime)
{
	currentAttackTime += deltaTime;
	startPos = { yggdrasil->GetLeftFistPos().x, yggdrasil->GetPosition().y - 200 };
	endPos = firstLeftPos;
	yggdrasil->SetLeftFistPos(sf::Vector2f::Lerp(startPos, endPos, currentAttackTime / readyDelay));
	startPos = { yggdrasil->GetRightFistPos().x, yggdrasil->GetPosition().y - 200 };
	endPos = firstRightPos;
	yggdrasil->SetRightFistPos(sf::Vector2f::Lerp(startPos, endPos, currentAttackTime / readyDelay));


	if (currentAttackTime >= readyDelay)
	{
		readyFist = false;
		onAttack = false;
	}

}

void YggdrasilFistAttackState::Recovery(float deltaTime)
{
	if (!switchFist)
	{
		currentRecoveryTime += deltaTime;
		yggdrasil->SetLeftFistPos(sf::Vector2f::Lerp(endPos, startPos, currentRecoveryTime / recoveryTime));

		if (currentRecoveryTime >= recoveryTime)
		{
			isAttack = false;
			isRecovery = false;
			currentRecoveryTime = 0.f;
			++currentAttackCount;
		}
	}
	else
	{
		currentRecoveryTime += deltaTime;
		yggdrasil->SetRightFistPos(sf::Vector2f::Lerp(endPos, startPos, currentRecoveryTime / recoveryTime));

		if (currentRecoveryTime >= recoveryTime)
		{
			isAttack = false;
			isRecovery = false;
			currentRecoveryTime = 0.f;
			++currentAttackCount;
		}
	}
}

void YggdrasilFistAttackState::CreateLeftEffect()
{
	AnimationGameObject* effect = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new AnimationGameObject("AttackEffect"), LayerType::Effect);
	Animation* animation(new Animation("animations/Enemy/Yggdrasil/Effects/yggdrasilHandSlamBoom.csv"));
	effect->GetAnimator()->AddAnimation(animation, "yggdrasilHandSlamBoom");
	effect->GetAnimator()->ChangeAnimation("yggdrasilHandSlamBoom");

	animation->SetAnimationEndEvent(std::bind(&GameObject::OnDestory, effect), animation->GetEndFrameCount());
	effect->SetPosition({ yggdrasil->GetLeftFistPos().x, 680.f });
	effect->SetScale(sf::Vector2f::one * 2.5f);

	effect->Awake();
	effect->Start();
}

void YggdrasilFistAttackState::CreateRightEffect()
{
	AnimationGameObject* effect = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new AnimationGameObject("AttackEffect"), LayerType::Effect);
	Animation* animation(new Animation("animations/Enemy/Yggdrasil/Effects/yggdrasilHandSlamBoom.csv"));
	effect->GetAnimator()->AddAnimation(animation, "yggdrasilHandSlamBoom");
	effect->GetAnimator()->ChangeAnimation("yggdrasilHandSlamBoom");

	animation->SetAnimationEndEvent(std::bind(&GameObject::OnDestory, effect), animation->GetEndFrameCount());
	effect->SetPosition({ yggdrasil->GetRightFistPos().x, 680.f });
	effect->SetScale(sf::Vector2f::one * 2.5f);

	effect->Awake();
	effect->Start();
}

void YggdrasilFistAttackState::Awake()
{
	YggdrasilBaseState::Awake();
	
}

void YggdrasilFistAttackState::Start()
{
	YggdrasilBaseState::Start();
	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("ElderEnt_FistSlam", "AudioClip/Stage1/ElderEnt_FistSlam.wav");
	changeOn = false;
}

void YggdrasilFistAttackState::Enter()
{

	YggdrasilBaseState::Enter();

	if (!yggdrasil->GetPhaseUp())
	{
		yggdrasil->SetAnimeLeftHand("phase1HandLeftTakedown", false);
		yggdrasil->SetAnimeRightHand("phase1HandRightTakedown", false);

		currentAttackCount = 0;
		attackCount = 2;

		readyFist = false;
		isAttack = false;
		isRecovery = false;
		isWait = false;
		switchFist = false;
		onAttack = true;
		hitBoxOn = false;

		currentAttackDelay = 0.f;
		currentAttackTime = 0.f;
		currentRecoveryTime = 0.f;
		switchFistDelay = 2.8f;
		readyTime = 0.f;
		waitTime = 1.f;

		readyDelay = 1.f;
		attackDelay = 2.f;
		attackTime = 0.3f;
		recoveryTime = 0.5f;
		switchFistTime = 2.8f;
	}
	else
	{
		yggdrasil->SetAnimeLeftHand("phase2HandLeftTakedown", false);
		yggdrasil->SetAnimeRightHand("phase2HandRightTakedown", false);

		currentAttackCount = 0;
		attackCount = 2;

		readyFist = false;
		isAttack = false;
		isRecovery = false;
		isWait = false;
		switchFist = false;
		onAttack = true;
		hitBoxOn = false;

		currentAttackDelay = 0.f;
		currentAttackTime = 0.f;
		currentRecoveryTime = 0.f;
		switchFistDelay = 1.f;
		readyTime = 0.f;

		readyDelay = 0.5f;
		attackDelay = 1.f;
		attackTime = 0.2f;
		recoveryTime = 0.2f;
		switchFistTime = 1.f;
		waitTime = 0.5f;
	}

	endPos = { player->GetPosition().x, -100.f };
	firstLeftPos = yggdrasil->GetLeftFistPos();
	firstRightPos = yggdrasil->GetRightFistPos();
}

void YggdrasilFistAttackState::Exit()
{
	YggdrasilBaseState::Exit();
}

void YggdrasilFistAttackState::Update(float deltaTime)
{
	if (yggdrasil->GetPhaseUp() && !changeOn)
	{
		Enter();
		changeOn = true;
	}
	if (!readyFist)
	{
		readyTime += deltaTime;
		ReadyFist(deltaTime);
		if (readyTime > readyDelay)
		{
			readyFist = true;
			currentAttackTime = 0.f;
		}
	}
	else
	{
		switchFistDelay += deltaTime;
	}
	if (player->GetPosition().x > yggdrasil->GetPosition().x && switchFistDelay >= switchFistTime)
	{
		switchFist = false;
	}
	else if (player->GetPosition().x < yggdrasil->GetPosition().x && switchFistDelay >= switchFistTime)
	{
		switchFist = true;
	}
	if (!switchFist)
	{
		if (!isAttack)
		{
			currentAttackDelay += deltaTime;
			if (yggdrasil->GetRightFistPos().y >= 700.f && events.size() != 0)
			{
				for (auto& posEvent : events)
				{
					if (posEvent)
						posEvent();
				}

				events.clear();
			}

			if (currentAttackDelay >= attackDelay)
			{
				startPos = yggdrasil->GetLeftFistPos();
				endPos = { player->GetPosition().x, 700.f };
				isAttack = true;
				currentAttackTime = 0.f;
			}
		}
		else
		{
			if (isRecovery)
			{
				Recovery(deltaTime);
			}
			else
			{
				if (!isWait)
				{
					StartAttack(deltaTime);
				}
				else
					EndAttackWait(deltaTime);
			}
		}
	}
	if (switchFist)
	{
		if (!isAttack)
		{
			currentAttackDelay += deltaTime;

			if (currentAttackDelay >= attackDelay)
			{
				startPos = yggdrasil->GetRightFistPos();
				endPos = { player->GetPosition().x, 700.f };
				isAttack = true;
				currentAttackTime = 0.f;
			}
		}
		else
		{
			if (isRecovery)
			{
				Recovery(deltaTime);
			}
			else
			{
				if (!isWait)
					StartAttack(deltaTime);
				else
					EndAttackWait(deltaTime);
			}
		}
	}


	if (currentAttackCount == attackCount)
	{
		EndFistPos(deltaTime);
	}

	if (!onAttack)
	{
		fsm->ChangeState(YggdrasilStateType::Idle);
	}
}

void YggdrasilFistAttackState::FixedUpdate(float fixedDeltaTime)
{
}

YggdrasilFistAttackState::YggdrasilFistAttackState(YggdrasilFSM* fsm)
	: YggdrasilBaseState(fsm, YggdrasilStateType::FistAttack)
{
	
}

