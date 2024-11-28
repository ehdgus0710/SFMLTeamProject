#include "stdafx.h"
#include "Player.h"

#include "Rigidbody.h"
#include "Animator.h"
#include "Collider.h"
#include "Animation.h"

#include "GameManager.h"
#include "Camera.h"
#include "InGameScoreUI.h"
#include "Head.h"
#include "PlayerBaseState.h"

Player::Player(const std::string& name)
	: AnimationGameObject(name)
	, fsm(this)
	, isJump(false)
	, currentStatus(2, 500.f, 200.f, 350.f)
	, hitTime(2.f)
	, currentHitTime(0.f)
	, reloadTime(0.2f)
	, currentReloadTime(0.f)
	, isReload(false)
	, isAttack(false)
	, isDead(false)
	, jumpCount(2)
	, currentJumpCount(2)
	, dashCount(2)
	, currentDashCount(2)
{
	rigidBody = new Rigidbody(this);
	rigidBody->SetGround(false);
	CreateCollider(ColliderType::Rectangle, ColliderLayer::Player);

	animator->LoadCsv("animators/littlebone.csv");
	animator->LoadCsv("animators/noheadlittlebone.csv");
}

Player::~Player()
{
}
void Player::TakeDamage()
{

	if (isHit)
		return;

	--currentStatus.hp;
	isHit = true;

	if (currentStatus.hp == 0)
	{
		isDead = true;
		fsm.ChangeState(PlayerStateType::Dead);
		return;
	}
	else
	{
		fsm.ChangeState(PlayerStateType::Hit);
	}

	currentHitTime = hitTime;
}

void Player::TakeDamage(float damage)
{
}

void Player::AddItem(ItemType itemType)
{
}
void Player::Attack()
{
}

void Player::OnAttackEnd()
{
}

void Player::OnDownJump()
{
	auto& targets = collider->GetCollisionTargets();
	bool isGround = false;
	for (auto& targetCollsion : targets)
	{
		if (targetCollsion->GetColliderLayer() == ColliderLayer::Wall)
		{
			Rectangle rect(collider->GetPosition(), collider->GetScale());
			Rectangle targetRect(targetCollsion->GetPosition(), targetCollsion->GetScale());

			if (rect.bottomPosition == targetRect.topPosition)
			{
				isGround = true;
				isJump = false;
				break;
			}
		}

	}

	if (!isGround)
	{
		rigidBody->SetGround(false);
		fsm.ChangeState(PlayerStateType::Falling);
	}
}


void Player::SetHeadPosition(sf::Vector2f pos)
{
	head->SetPosition(pos);
}

sf::Vector2f Player::GetHeadPosition()
{
	return head->GetPosition();
}

void Player::SetOnHeadSkill1(bool onoff)
{
	head->SetHeadSkillOn(onoff);
}

bool Player::GetOnHeadSkill1()
{
	return head->GetHeadSkillOn();
}

void Player::Awake()
{
	AnimationGameObject::Awake();
	currentDashCount = dashCount;
	currentJumpCount = jumpCount;
	dashDelayTime = 1.3f;
}

void Player::Start()
{
	AnimationGameObject::Start();
	fsm.Start();
	animator->ChangeAnimation("noheadlittleboneIdle", true);

	head = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new Head("Head"), LayerType::Player);
	head->SetPlayer(this);
	head->Awake();
	head->GetCollider()->SetScale({ 50.f,50.f });
	head->SetHeadSkillOn(false);

	skill1OnTime = 0.2f;
}

void Player::Update(const float& deltaTime)
{
	fsm.Update(deltaTime);
	animator->Update(deltaTime);
	currentTime += deltaTime;
	if (head->GetHeadSkillOn())
	{

		if(currentTime >= skill1OnTime)
			head->GetRigidbody()->SetActive(true);
		else
			head->SetPosition(sf::Vector2f::Lerp(skill1StartPos, skillEndPos, currentTime / skill1OnTime));

	}
	else
	{
		head->SetPosition(GetPosition());
	}

	if (isHit)
	{
		currentHitTime -= deltaTime;

		if (currentHitTime <= 0.f)
		{
			isHit = false;
			currentHitTime = 0.f;
		}
	}

	if (currentDashCount <= 0)
	{
		currentDashDelayTime += deltaTime;
		if (currentDashDelayTime > dashDelayTime)
		{
			currentDashCount = dashCount;
			currentDashDelayTime = 0.f;
		}
	}

	if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::A))
	{
		skillEndPos = GetPosition() + (IsFlipX() ? sf::Vector2f::left : sf::Vector2f::right) * 800.f;
		skill1StartPos = GetPosition();
		head->SetHeadSkillOn(true);
		head->GetRigidbody()->SetActive(false);
		currentTime = 0.f;
	}

	if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::S))
	{
		head->SetHeadSkillOn(false);
		SetPosition(head->GetPosition());
	}

	if (fsm.GetCurrentStateType() != PlayerStateType::Falling && rigidBody->GetCurrentVelocity().y > 0.f)
		fsm.ChangeState(PlayerStateType::Falling);
}

void Player::FixedUpdate(const float& deltaTime)
{
	fsm.FixedUpdate(deltaTime);
	rigidBody->FixedUpdate(deltaTime);
}

void Player::LateUpdate(const float& deltaTime)
{
	fsm.LateUpdate(deltaTime);
}

void Player::OnCollisionEnter(Collider* target)
{
	if (target->GetOwner() == head)
	{
		fsm.GetCurrentState()->SetChangeAnimationKey(0);
	}
}
void Player::OnCollisionStay(Collider* target)
{
}
void Player::OnCollisionEnd(Collider* target)
{
	if (target->GetColliderLayer() == ColliderLayer::Wall || target->GetColliderLayer() == ColliderLayer::Scaffolding)
	{
		auto& targets = collider->GetCollisionTargets();
		bool isGround = false;
		for (auto& targetCollsion : targets)
		{
			if (targetCollsion == target)
				continue;

			Rectangle rect(collider->GetPosition(), collider->GetScale());
			Rectangle targetRect(targetCollsion->GetPosition(), targetCollsion->GetScale());

			if (rect.bottomPosition == targetRect.topPosition)
			{
				isGround = true;
				isJump = false;
				break;
			}
		}

		if (!isGround)
		{
			rigidBody->SetGround(false);
			currentJumpCount = 1;
		}
		else
		{
			currentJumpCount = jumpCount;
			head->SetHeadSkillOn(false);
		}
	}

}

PlayerSaveData Player::GetPlayerSaveData() const
{
	return PlayerSaveData({ this->GetGameObjectSaveData(), currentStatus });
}

void Player::LoadData(const PlayerSaveData& data)
{
	LoadGameObjectData(data.gameObjectSaveData);
	currentStatus = data.status;
}
