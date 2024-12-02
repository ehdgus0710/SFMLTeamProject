#include "stdafx.h"
#include "YggdrasilEnergyBallBig.h"

#include "Rigidbody.h"
#include "Animator.h"
#include "Collider.h"
#include "Animation.h"

#include "Player.h"

YggdrasilEnergyBallBig::YggdrasilEnergyBallBig(const std::string& name)
	: AnimationGameObject(name)
{
	rigidBody = new Rigidbody(this);
	rigidBody->SetGround(false);
	CreateCollider(ColliderType::Rectangle, ColliderLayer::Boss, sf::Vector2f::zero, sf::Vector2f(100.f, 100.f));
}


YggdrasilEnergyBallBig::~YggdrasilEnergyBallBig()
{
}


void YggdrasilEnergyBallBig::Awake()
{
	AnimationGameObject::Awake();
}

void YggdrasilEnergyBallBig::Start()
{
	AnimationGameObject::Start();
}

void YggdrasilEnergyBallBig::Update(const float& deltaTime)
{
}

void YggdrasilEnergyBallBig::FixedUpdate(const float& deltaTime)
{
	rigidBody->FixedUpdate(deltaTime);
}

void YggdrasilEnergyBallBig::LateUpdate(const float& deltaTime)
{
}

void YggdrasilEnergyBallBig::OnCollisionEnter(Collider* target)
{
}

void YggdrasilEnergyBallBig::OnCollisionStay(Collider* target)
{
}

void YggdrasilEnergyBallBig::OnCollisionEnd(Collider* target)
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

void YggdrasilEnergyBallBig::fire()
{
}

void YggdrasilEnergyBallBig::SetYggdrasil(Yggdrasil* player)
{
}

void YggdrasilEnergyBallBig::SetPlayer(Player* player)
{
	this->player = player;
}

