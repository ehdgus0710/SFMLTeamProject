#include "stdafx.h"
#include "StarObject.h"
#include "Rigidbody.h"
#include "Animator.h"
#include "Collider.h"
#include "Animation.h"
#include "Player.h"

StarObject::StarObject()
	: ItemObject(ItemType::Star, "Items", "Star")
	, moveSpeed(500.f)
	, moveDirection(sf::Vector2f::right)
	, lifeTime(3.f)
	, currentLifeTime(0.f)
	, isJump(false)

{
	rigidBody = new Rigidbody(this);
	rigidBody->SetGround(true);

	CreateAnimator();
	animator->LoadCsv("animators/star.csv");
}

void StarObject::Start()
{
	SetScale(scale);
	SetPosition(position);
	SetRotation(rotation);

	SetOrigin(originPreset);
	animator->Start();
	collider->SetOwnerScale({ (sf::Vector2f)animator->GetCurrentAnimation()->GetFrameInfo()[0].rectSize });
	collider->Reset();
	animator->ChangeAnimation("star", true);
}

void StarObject::Update(const float& deltaTime)
{
	animator->Update(deltaTime);

	if (isCreateEvent)
	{
		position += sf::Vector2f::up * speed * deltaTime;
		if (position.y <= createEndPosition.y)
		{
			isCreateEvent = false;
			collider->SetActive(true);
			position.y = createEndPosition.y;
		}

		SetPosition(position);
	}
}
void StarObject::FixedUpdate(const float& deltaTime)
{
	if (!isCreateEvent)
	{
		rigidBody->SetVelocity({ speed * moveDirection.x,  rigidBody->GetCurrentVelocity().y });
		rigidBody->FixedUpdate(deltaTime);
	}
}

void StarObject::OnCollisionEnter(Collider* target)
{
	if (target->GetColliderLayer() == ColliderLayer::Block || target->GetColliderLayer() == ColliderLayer::Wall)
	{
		GameObject* object = target->GetOwner();
		Rigidbody* targetRigidbody = target->GetOwner()->GetRigidbody();

		Rectangle rect(collider->GetPosition(), collider->GetScale());
		Rectangle targetRect(target->GetPosition(), target->GetScale());

		float prevPositionY = rigidBody->GetPrevDropSpeed();

		if (prevPositionY  != 0.f && !(rect.bottomPosition - prevPositionY < targetRect.topPosition))
		{
			moveDirection.x *= -1.f;
		}
	}
	else if (target->GetColliderLayer() == ColliderLayer::Player)
	{
		Player* player = (Player*)target->GetOwner();
		player->AddItem(itemType);
		SetDestory(true);
	}
}

void StarObject::OnCollisionStay(Collider* target)
{
}

void StarObject::OnCollisionEnd(Collider* target)
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
		{
			rigidBody->SetGround(false);

			if(!isJump)
				rigidBody->AddDropSpeed(30.f);
			isJump = true;
		}
	}
}

void StarObject::CreateAnimator()
{
	if (animator == nullptr)
		animator = new Animator(this, sprite);
}
