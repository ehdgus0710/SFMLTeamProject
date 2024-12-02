#include "stdafx.h"
#include "YggdrasilEnergyBallSmall.h"
#include "Rigidbody.h"
#include "Animator.h"
#include "Collider.h"
#include "Animation.h"

#include "Player.h"

YggdrasilEnergyBallSmall::YggdrasilEnergyBallSmall(const std::string& name)
	: AnimationGameObject(name)
{
	rigidBody = new Rigidbody(this);
	rigidBody->SetGround(false);
	CreateCollider(ColliderType::Rectangle, ColliderLayer::EnemyBullet, sf::Vector2f::zero, sf::Vector2f(100.f, 100.f));

	Animation* animation = new Animation("animations/Enemy/yggdrasil/Effects/EnergyBomb.csv");
	animator->AddAnimation(animation, "EnergyBomb");
	animator->ChangeAnimation("EnergyBomb", true);
}


YggdrasilEnergyBallSmall::~YggdrasilEnergyBallSmall()
{
}


void YggdrasilEnergyBallSmall::Awake()
{
	AnimationGameObject::Awake();
}

void YggdrasilEnergyBallSmall::Start()
{
	AnimationGameObject::Start();
}

void YggdrasilEnergyBallSmall::Update(const float& deltaTime)
{
	animator->Update(deltaTime);
}

void YggdrasilEnergyBallSmall::FixedUpdate(const float& deltaTime)
{
	rigidBody->FixedUpdate(deltaTime);
}

void YggdrasilEnergyBallSmall::LateUpdate(const float& deltaTime)
{
}

void YggdrasilEnergyBallSmall::OnCollisionEnter(Collider* target)
{
}

void YggdrasilEnergyBallSmall::OnCollisionStay(Collider* target)
{
}

void YggdrasilEnergyBallSmall::OnCollisionEnd(Collider* target)
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

void YggdrasilEnergyBallSmall::fire()
{
}

void YggdrasilEnergyBallSmall::SetAniEnergyBallSmall(std::string name, bool loop)
{
	animator->ChangeAnimation(name, loop);
}
void YggdrasilEnergyBallSmall::SetYggdrasil(Yggdrasil* yggdrasil)
{
}
void YggdrasilEnergyBallSmall::SetPlayer(Player* player)
{
	this->player = player;
}