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
	CreateCollider(ColliderType::Rectangle, ColliderLayer::EnemyBullet, sf::Vector2f::zero, sf::Vector2f(100.f, 100.f));

	Animation* animation = new Animation("animations/Enemy/yggdrasil/Effects/EnergyBomb.csv");
	animator->AddAnimation(animation, "EnergyBomb");
	animator->ChangeAnimation("EnergyBomb", true);
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
	animator->Update(deltaTime);
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

void YggdrasilEnergyBallBig::SetAniEnergyBallBig(std::string name, bool loop)
{
	animator->ChangeAnimation(name, loop);
}

void YggdrasilEnergyBallBig::SetYggdrasil(Yggdrasil* yggdrasil)
{
}

void YggdrasilEnergyBallBig::SetPlayer(Player* player)
{
	this->player = player;
}

