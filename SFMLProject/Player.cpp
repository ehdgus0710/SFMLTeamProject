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
#include "PlayerUIHub.h"

Player::Player(const std::string& name)
	: AnimationGameObject(name)
	, fsm(this)
	, isJump(false)
	, currentStatus(150.f, 500.f, 200.f, 350.f)
	, reloadTime(0.2f)
	, currentReloadTime(0.f)
	, isReload(false)
	, isAttack(false)
	, isDead(false)
	, jumpCount(2)
	, currentJumpCount(2)
	, dashCount(2)
	, currentDashCount(2)
	, isNoneHead(false)
	, currentSkill1CoolTime(0.f)
	, currentSkill2CoolTime(0.f)
	, skill1CoolTime(2.f)
	, skill2CoolTime(3.f)
	, isSkll1CoolTime(false)
	, isSkll2CoolTime(false)
	, skullType(SkullType::Littlebone)
	
{	
	rigidBody = new Rigidbody(this);
	rigidBody->SetGround(false);
	CreateCollider(ColliderType::Rectangle, ColliderLayer::Player);

	animator->LoadCsv("animators/littlebone.csv");
	animator->LoadCsv("animators/noheadlittlebone.csv");

	InputManager::GetInstance().BindKey(sf::Keyboard::Numpad7);
}

Player::~Player()
{
}

void Player::TakeDamage(float damage)
{
	currentStatus.hp -= damage;

	if (currentStatus.hp <= 0.f)
	{
		currentStatus.hp = 0.f;
		//isDead = true;
		//fsm.ChangeState(PlayerStateType::Dead);
	}

	if (changeHpAction != nullptr)
		changeHpAction(currentStatus.hp, currentStatus.maxHp);
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

void Player::OnThrowHead()
{
	head->ThrowHead();
	head->SetActive(true);
	isNoneHead = true;
}

void Player::OnGetHead()
{
	head->SetActive(false);
	isNoneHead = false;
	fsm.GetCurrentState()->SetChangeAnimationKey(0);
}

void Player::OnSkill1CoolTime()
{
	isSkll1CoolTime = true;
	currentSkill1CoolTime = 0.f;
}

void Player::OnSkill2CoolTime()
{
	isSkll2CoolTime = true;
	currentSkill2CoolTime = 0.f;
}


void Player::SetHeadPosition(sf::Vector2f pos)
{
	head->SetPosition(pos);
}

sf::Vector2f Player::GetHeadPosition()
{
	return head->GetPosition();
}
void Player::AddHp(float hp)
{
	currentStatus.hp += hp;

	if (currentStatus.hp > currentStatus.maxHp)
		currentStatus.hp = currentStatus.maxHp;

	if (changeHpAction)
		changeHpAction(currentStatus.hp, currentStatus.maxHp);
}
void Player::SetMaxHp(float maxHp)
{
	currentStatus.maxHp = maxHp;

	if (changeHpAction)
		changeHpAction(currentStatus.hp, currentStatus.maxHp);
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

	SetScale({ 3.f,3.f });
	collider->SetScale({ 16.f,32.f });
	collider->SetOffsetPosition({ 0.f, -5.f });

	head = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new Head("Head"), LayerType::PlayerBullet);
	head->SetPlayer(this);
	head->Awake();
	head->SetActive(false);

	PlayerUIHub* playerUIHub = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new PlayerUIHub("PlayerUiFrame"), LayerType::InGameUI);

	playerUIHub->SetOrigin(Origins::BottomLeft);
	playerUIHub->SetScale({ 3.5f,3.5f });
	playerUIHub->SetPosition({ 0, 1075.f });
}

void Player::Update(const float& deltaTime)
{
	fsm.Update(deltaTime);
	animator->Update(deltaTime);
	if (currentDashCount <= 0)
	{
		currentDashDelayTime += deltaTime;
		if (currentDashDelayTime > dashDelayTime)
		{
			currentDashCount = dashCount;
			currentDashDelayTime = 0.f;
		}
	}

	if (isSkll1CoolTime)
	{
		currentSkill1CoolTime += deltaTime;

		if (currentSkill1CoolTime >= skill1CoolTime)
			isSkll1CoolTime = false;
	}

	if (isSkll2CoolTime)
	{
		currentSkill2CoolTime += deltaTime;

		if (currentSkill2CoolTime >= skill2CoolTime)
			isSkll2CoolTime = false;
	}

	if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::A))
	{
		if(!isSkll1CoolTime && fsm.GetCurrentStateType() != PlayerStateType::Skill1 && fsm.GetCurrentStateType() != PlayerStateType::Dead)
			fsm.ChangeState(PlayerStateType::Skill1);
	}

	if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::S))
	{
		if (!isSkll2CoolTime && fsm.GetCurrentStateType() != PlayerStateType::Skill2 && fsm.GetCurrentStateType() != PlayerStateType::Dead)
			fsm.ChangeState(PlayerStateType::Skill2);
	}

	if (fsm.GetCurrentStateType() != PlayerStateType::Falling && fsm.GetCurrentStateType() != PlayerStateType::JumpAttack && rigidBody->GetActive() && rigidBody->GetCurrentVelocity().y > 0.f)
		fsm.ChangeState(PlayerStateType::Falling);

	if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::Numpad7))
	{
		TakeDamage(10);
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
	if (target->GetOwner() == head && !head->IsOnSkill())
		OnGetHead();
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
