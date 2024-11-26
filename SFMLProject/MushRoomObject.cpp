#include "stdafx.h"
#include "MushRoomObject.h"
#include "Rigidbody.h"
#include "Collider.h"
#include "Player.h"

MushRoomObject::MushRoomObject()
	: ItemObject(ItemType::MushRoom, "Items", "MushRoom")
	, moveDirection(sf::Vector2f::right)
	, moveSpeed(100.f)
{
	textureUVRect = { 0,0,16,16 };
	scale = { 4.f,4.f };
	rigidBody = new Rigidbody(this);
	rigidBody->SetGround(true);
}



void MushRoomObject::Start()
{
	SetScale(scale);
	SetPosition(position);
	SetRotation(rotation);

	sprite.setTexture(ResourcesManager<sf::Texture>::GetInstance().Get(textureID), true);
	sprite.setTextureRect(textureUVRect);

	SetOrigin(originPreset);
	collider->Reset();
	collider->SetScale({ 64.f,64.f });
}

void MushRoomObject::FixedUpdate(const float& deltaTime)
{
	if (!isCreateEvent)
	{
		rigidBody->SetVelocity({ speed * moveDirection.x,  rigidBody->GetCurrentVelocity().y});
		rigidBody->FixedUpdate(deltaTime);
	}
}

void MushRoomObject::OnCollisionEnter(Collider* target)
{
	if (target->GetColliderLayer() == ColliderLayer::Block || target->GetColliderLayer() == ColliderLayer::Wall)
	{
		GameObject* object = target->GetOwner();
		Rigidbody* targetRigidbody = target->GetOwner()->GetRigidbody();

		Rectangle rect(collider->GetPosition(), collider->GetScale());
		Rectangle targetRect(target->GetPosition(), target->GetScale());

		if (rect.bottomPosition != targetRect.topPosition)
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

void MushRoomObject::OnCollisionStay(Collider* target)
{
}

void MushRoomObject::OnCollisionEnd(Collider* target)
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
			rigidBody->AddDropSpeed(30.f);
		}
	}
}
