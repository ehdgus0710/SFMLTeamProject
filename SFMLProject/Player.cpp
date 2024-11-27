#include "stdafx.h"
#include "Player.h"

#include "Rigidbody.h"
#include "Animator.h"
#include "Collider.h"
#include "Animation.h"

#include "GameManager.h"
#include "Camera.h"
#include "InGameScoreUI.h"

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
	CreateAnimator();
	CreateCollider(ColliderType::Rectangle, ColliderLayer::Player);
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

void Player::AddItem(ItemType itemType)
{
}
void Player::Attack()
{
}

void Player::OnAttackEnd()
{
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
}

void Player::Update(const float& deltaTime)
{
	fsm.Update(deltaTime);
	animator->Update(deltaTime);

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
}
void Player::OnCollisionStay(Collider* target)
{
}
void Player::OnCollisionEnd(Collider* target)
{
	if (target->GetColliderLayer() == ColliderLayer::Wall)
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
			if(fsm.GetCurrentStateType() != PlayerStateType::Dash && rigidBody->GetCurrentVelocity().y > 0.f)
				fsm.ChangeState(PlayerStateType::Falling);
		}
	}
	
}

PlayerSaveData Player::GetPlayerSaveData() const
{
	return PlayerSaveData({this->GetGameObjectSaveData(), currentStatus});
}

void Player::LoadData(const PlayerSaveData& data)
{
	LoadGameObjectData(data.gameObjectSaveData);
	currentStatus = data.status;
}
