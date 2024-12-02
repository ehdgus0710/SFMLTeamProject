#include "stdafx.h"
#include "YggdrasilBody.h"

#include "Rigidbody.h"
#include "Animator.h"
#include "Collider.h"
#include "Animation.h"

#include "Player.h"

void YggdrasilBody::Awake()
{
	AnimationGameObject::Awake();
	skillOn = false;
}

void YggdrasilBody::Start()
{
	AnimationGameObject::Start();
}

void YggdrasilBody::Update(const float& deltaTime)
{
	rigidBody->Update(deltaTime);
}

void YggdrasilBody::FixedUpdate(const float& deltaTime)
{
	rigidBody->FixedUpdate(deltaTime);
}

void YggdrasilBody::LateUpdate(const float& deltaTime)
{
}

void YggdrasilBody::OnCollisionEnter(Collider* target)
{
}

void YggdrasilBody::OnCollisionStay(Collider* target)
{
}

void YggdrasilBody::OnCollisionEnd(Collider* target)
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

void YggdrasilBody::fire()
{
}

void YggdrasilBody::SetPlayer(Player* player)
{
	this->player = player;

}

PlayerSaveData YggdrasilBody::GetPlayerSaveData() const
{
	return PlayerSaveData();
}

void YggdrasilBody::LoadData(const PlayerSaveData& data)
{
}

YggdrasilBody::YggdrasilBody(const std::string& name)
	: AnimationGameObject(name)
	, skillOn(false)
{
	rigidBody = new Rigidbody(this);
	rigidBody->SetGround(false);
	CreateCollider(ColliderType::Rectangle, ColliderLayer::Boss, sf::Vector2f(10.f, 10.f), sf::Vector2f(100.f, 100.f));
}

YggdrasilBody::~YggdrasilBody()
{
}
