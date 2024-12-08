#include "stdafx.h"
#include "YggdrasilRightHand.h"

#include "Rigidbody.h"
#include "Animator.h"
#include "Collider.h"
#include "Animation.h"

#include "Player.h"


YggdrasilRightHand::YggdrasilRightHand(const std::string& name)
	: AnimationGameObject(name)
	, skillOn(false)
{
	rigidBody = new Rigidbody(this);
	rigidBody->SetGround(false);
	rigidBody->Disable();
	CreateCollider(ColliderType::Rectangle, ColliderLayer::EnemyBullet, sf::Vector2f::zero, sf::Vector2f(100.f, 100.f));
	SetScale({ 3.5f, 3.5f });
	animator->LoadCsv("animators/yggdrasilHandRight.csv");
}

YggdrasilRightHand::~YggdrasilRightHand()
{
}

void YggdrasilRightHand::Awake()
{
	AnimationGameObject::Awake();
	skillOn = false;
}

void YggdrasilRightHand::Start()
{
	AnimationGameObject::Start();
	animator->ChangeAnimation("phase1HandRightIdle", true);
}

void YggdrasilRightHand::Update(const float& deltaTime)
{
	animator->Update(deltaTime);
}

void YggdrasilRightHand::FixedUpdate(const float& deltaTime)
{
	rigidBody->FixedUpdate(deltaTime);
}

void YggdrasilRightHand::LateUpdate(const float& deltaTime)
{
}

void YggdrasilRightHand::OnCollisionEnter(Collider* target)
{
}

void YggdrasilRightHand::OnCollisionStay(Collider* target)
{
}

void YggdrasilRightHand::OnCollisionEnd(Collider* target)
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
				break;
			}
		}

		if (!isGround)
		{
			rigidBody->SetGround(false);
		}
	}
}

void YggdrasilRightHand::fire()
{
}

void YggdrasilRightHand::SetAniRightHand(std::string name, bool loop)
{
	animator->ChangeAnimation(name, loop);
}

void YggdrasilRightHand::SetYggdrasil(Yggdrasil* yggdrasil)
{
}

void YggdrasilRightHand::SetPlayer(Player* player)
{
	this->player = player;
}