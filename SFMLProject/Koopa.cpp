#include "stdafx.h"
#include "Koopa.h"

#include "Animator.h"
#include "Animation.h"
#include "Collider.h"
#include "Collision.h"
#include "Player.h"
#include "Rigidbody.h"
#include "KoopaFSM.h"
#include "KooparHammerBullet.h"
#include "WallCollisionObject.h"

Koopa::Koopa(const std::string& name)
	: Enemy(EnemyType::Koopa, name)
	, player(nullptr)
	, currentJumpTime(0.f)
	, jumpTime(3.f)
	, isJump(false)
	, isDead(false)
	, currentHammerIndex(0)
	, createHammerCount(6)
	, currentHammerFiringTime(0.f)
	, hammerFiringTime(0.1f)
	, isCreateHammer(false)
	, isEndHammerFiring(true)
	, hammerPosition({-40.f, -62.f})
	, isLabberDead(false)
	, wallObject(nullptr)
{
	fsm = new KoopaFSM(this);

	CreateAnimator();
	animator->LoadCsv("animators/koopa.csv");
	CreateCollider(ColliderType::Rectangle, ColliderLayer::Enemy);
	currentStatus.maxHp = 5;
	currentStatus.hp = currentStatus.maxHp;
}

Koopa::~Koopa()
{
	if (fsm != nullptr)
	{
		delete fsm;
	}
}

void Koopa::OnJump()
{
	isJump = true;
	rigidBody->SetVelocity({ rigidBody->GetCurrentVelocity().x  , -900.f});
	rigidBody->SetGround(false);
	currentJumpTime = 0.f;
}

void Koopa::OnDead()
{
	if (isDead)
		return;

	isDead = true;
	fsm->ChangeState(EnemyStateType::Dead);
}

void Koopa::OnCreateHammer()
{
	if (!isEndHammerFiring)
		return;

	Scene* currentScene = SceneManager::GetInstance().GetCurrentScene();

	for (int i = 0; i < createHammerCount; ++i)
	{
		hammers.push_back(currentScene->AddGameObject(new KooparHammerBullet(), LayerType::EnemyBullet));
		hammers[i]->Start();
	}


	currentHammerIndex = createHammerCount - 1;
	currentHammerFiringTime = 0.f;

	isCreateHammer = true;
}

void Koopa::HammerFiring(const float& deltaTime)
{
	currentHammerFiringTime += deltaTime;

	if (currentHammerFiringTime >= hammerFiringTime)
	{
		hammers[currentHammerIndex]->SetMoveDirection({ isFlipX ? 1.f : -1.f , 0.f });
		hammers[currentHammerIndex--]->OnFiring();
		hammers.pop_back();
		currentHammerFiringTime = 0.f;

		if (currentHammerIndex == -1)
		{
			hammers.clear();
			isEndHammerFiring = true;
			isCreateHammer = false;
		}
	}
}

void Koopa::DisableScaffoldingCollision()
{
	wallObject->OnDestory();
}

void Koopa::Awake()
{
	// animator->ChangeAnimation("goombaMove", true);
}

void Koopa::Start()
{
	Enemy::Start();

	Scene* scene = SceneManager::GetInstance().GetCurrentScene();
	wallObject = (WallCollisionObject*)scene->FindGameObject("ScaffoldingWall");

	fsm->ChangeState(EnemyStateType::Idle);
	GetCollider()->SetScale({ (sf::Vector2f)animator->GetCurrentAnimation()->GetFrameInfo()[0].rectSize });

	player = (Player*)(SceneManager::GetInstance().GetCurrentScene()->FindGameObject("Player", LayerType::Player));
	currentJumpTime = jumpTime;
}

void Koopa::Update(const float& deltaTime)
{
	Enemy::Update(deltaTime);

	if (isDead)
		return;

	float distance = abs(abs(player->GetPosition().x) - abs(position.x));
	if (distance < 400.f)
	{
		if (position.x < player->GetPosition().x)
			rigidBody->SetVelocity({ -currentStatus.speed , rigidBody->GetCurrentVelocity().y });
		else
			rigidBody->SetVelocity({ currentStatus.speed  , rigidBody->GetCurrentVelocity().y });
	}
	else
	{
		if (position.x < player->GetPosition().x)
			rigidBody->SetVelocity({ currentStatus.speed  , rigidBody->GetCurrentVelocity().y });
		else
			rigidBody->SetVelocity({ -currentStatus.speed  , rigidBody->GetCurrentVelocity().y });
	}

	if ((!isFlipX && position.x < player->GetPosition().x) || (isFlipX && position.x > player->GetPosition().x))
		OnFlipX();


	if (!isJump)
	{
		currentJumpTime += deltaTime;

		if (currentJumpTime >= jumpTime)
		{
			OnCreateHammer();
			OnJump();
		}
	}

	if (isJump && rigidBody->IsGround())
		isJump = false;

	if (isCreateHammer)
	{
		HammerFiring(deltaTime);

		sf::Vector2f currenthammerPos = hammerPosition;

		if (IsFlipX())
			currenthammerPos.x *= -1.f;

		for (auto& hammer : hammers)
		{
			hammer->SetPosition(position + currenthammerPos);
		}
	}
}

void Koopa::OnCollisionEnter(Collider* target)
{
}

void Koopa::OnCollisionStay(Collider* target)
{
	if (target->GetColliderLayer() == ColliderLayer::Player)
	{
		((Player*)target->GetOwner())->TakeDamage();
	}
}

void Koopa::OnCollisionEnd(Collider* target)
{
	if (target->GetColliderLayer() == ColliderLayer::Wall || target->GetColliderLayer() == ColliderLayer::Block)
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
				break;
			}

		}

		if (!isGround)
			rigidBody->SetGround(false);
	}
}