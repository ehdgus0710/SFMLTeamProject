#include "stdafx.h"
#include "YggdrasilMouth.h"

#include "Rigidbody.h"
#include "Animator.h"
#include "Collider.h"
#include "Animation.h"

#include "Player.h"


YggdrasilMouth::YggdrasilMouth(const std::string& name)
	: AnimationGameObject(name)
	, skillOn(false)
{
	rigidBody = new Rigidbody(this);
	rigidBody->SetGround(false);
	CreateCollider(ColliderType::Rectangle, ColliderLayer::Boss, sf::Vector2f::zero, sf::Vector2f(100.f, 100.f));
	SetScale({ 3.5f, 3.5f });
	animator->LoadCsv("animators/yggdrasilMouth.csv");

}

YggdrasilMouth::~YggdrasilMouth()
{
}

void YggdrasilMouth::Awake()
{
	AnimationGameObject::Awake();
	skillOn = false;
}

void YggdrasilMouth::Start()
{
	AnimationGameObject::Start();
	animator->ChangeAnimation("yggdrasilPhase1Mouth", true);
}

void YggdrasilMouth::Update(const float& deltaTime)
{
	animator->Update(deltaTime);
}

void YggdrasilMouth::FixedUpdate(const float& deltaTime)
{
	rigidBody->FixedUpdate(deltaTime);
}

void YggdrasilMouth::LateUpdate(const float& deltaTime)
{
}

void YggdrasilMouth::SetAniMouth(std::string name, bool loop)
{
	animator->ChangeAnimation(name, loop);
}

void YggdrasilMouth::OnCollisionEnter(Collider* target)
{
}

void YggdrasilMouth::OnCollisionStay(Collider* target)
{
}

void YggdrasilMouth::OnCollisionEnd(Collider* target)
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

void YggdrasilMouth::fire()
{
}

void YggdrasilMouth::SetYggdrasil(Yggdrasil* player)
{
}

void YggdrasilMouth::SetPlayer(Player* player)
{
	this->player = player;

}

PlayerSaveData YggdrasilMouth::GetPlayerSaveData() const
{
	return PlayerSaveData();
}

void YggdrasilMouth::LoadData(const PlayerSaveData& data)
{
}