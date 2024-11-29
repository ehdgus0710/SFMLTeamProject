#include "stdafx.h"
#include "Head.h"

#include "Rigidbody.h"
#include "Animator.h"
#include "Collider.h"
#include "Animation.h"

#include "Player.h"

Head::Head(const std::string& name)
	: AnimationGameObject(name)
	, skillOn(false)
{
	rigidBody = new Rigidbody(this);
	rigidBody->SetGround(false);
	CreateCollider(ColliderType::Rectangle, ColliderLayer::Player, sf::Vector2f(10.f, 10.f), sf::Vector2f(1.5f, 1.5f));
}

Head::~Head()
{
}
void Head::Awake()
{
	AnimationGameObject::Awake();
	skillOn = false;
}

void Head::Start()
{
	AnimationGameObject::Start();
	
}

void Head::Update(const float& deltaTime)
{
	rigidBody->Update(deltaTime);
}

void Head::FixedUpdate(const float& deltaTime)
{
	rigidBody->FixedUpdate(deltaTime);
}

void Head::LateUpdate(const float& deltaTime)
{
}

void Head::OnCollisionEnter(Collider* target)
{
}

void Head::OnCollisionStay(Collider* target)
{
}

void Head::OnCollisionEnd(Collider* target)
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

void Head::fire()
{
}

void Head::SetPlayer(Player* player)
{
	this->player = player;
}

PlayerSaveData Head::GetPlayerSaveData() const
{
	return PlayerSaveData();
}

void Head::LoadData(const PlayerSaveData& data)
{
}

