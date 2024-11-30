#include "stdafx.h"
#include "YggdrasilLeftHand.h"

#include "Rigidbody.h"
#include "Animator.h"
#include "Collider.h"
#include "Animation.h"

#include "Player.h"

void YggdrasilLeftHand::Awake()
{
    AnimationGameObject::Awake();
    skillOn = false;
}

void YggdrasilLeftHand::Start()
{
    AnimationGameObject::Start();
}

void YggdrasilLeftHand::Update(const float& deltaTime)
{
    rigidBody->Update(deltaTime);
}

void YggdrasilLeftHand::FixedUpdate(const float& deltaTime)
{
    rigidBody->FixedUpdate(deltaTime);
}

void YggdrasilLeftHand::LateUpdate(const float& deltaTime)
{
}

void YggdrasilLeftHand::OnCollisionEnter(Collider* target)
{
}

void YggdrasilLeftHand::OnCollisionStay(Collider* target)
{
}

void YggdrasilLeftHand::OnCollisionEnd(Collider* target)
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

void YggdrasilLeftHand::fire()
{
}

void YggdrasilLeftHand::SetYggdrasil(Yggdrasil* yggdrasil)
{
}

void YggdrasilLeftHand::SetPlayer(Player* player)
{
	this->player = player;

}

PlayerSaveData YggdrasilLeftHand::GetPlayerSaveData() const
{
    return PlayerSaveData();
}

void YggdrasilLeftHand::LoadData(const PlayerSaveData& data)
{
}

YggdrasilLeftHand::YggdrasilLeftHand(const std::string& name)
	: AnimationGameObject(name)
	, skillOn(false)
{
	rigidBody = new Rigidbody(this);
	rigidBody->SetGround(false);
	CreateCollider(ColliderType::Rectangle, ColliderLayer::Boss, sf::Vector2f::zero, sf::Vector2f(100.f, 100.f));
}

YggdrasilLeftHand::~YggdrasilLeftHand()
{
}
