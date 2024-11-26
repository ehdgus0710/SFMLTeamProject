#include "stdafx.h"
#include "WallCollisionObject.h"
#include "Collider.h"
#include "Collision.h"

#include "Rigidbody.h"
#include "Player.h"
#include "Enemy.h"

int WallCollisionObject::wallID = 0;

WallCollisionObject::WallCollisionObject(const std::string& name)
    : GameObject(name + std::to_string(wallID++))
{
    originPreset = Origins::MiddleCenter;
    CreateCollider(ColliderType::Rectangle, ColliderLayer::Wall);
}

WallCollisionObject::~WallCollisionObject()
{
}


void WallCollisionObject::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;
	collider->SetOwnerScale(scale);
    SetOrigin(originPreset);
}

void WallCollisionObject::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	collider->SetPosition(position);
}

void WallCollisionObject::SetOrigin(Origins preset)
{
	originPreset = preset;
    collider->SetOrigin(preset);
}

sf::FloatRect WallCollisionObject::GetLocalBounds() const
{
    return collider->GetLocalBounds();
}

sf::FloatRect WallCollisionObject::GetGlobalBounds() const
{
    return collider->GetGlobalBounds();
}
void WallCollisionObject::Start()
{
	SetScale(scale);
	SetPosition(position);
	SetRotation(rotation);
	SetOrigin(originPreset);
	collider->Reset();
}

void WallCollisionObject::OnCollisionEnter(Collider* target)
{
	if (target->GetColliderLayer() == ColliderLayer::Player || target->GetColliderLayer() == ColliderLayer::Enemy)
	{
		GameObject* object = target->GetOwner();

		sf::Vector2f targetPosition = target->GetPosition();

		Rectangle rect(collider->GetPosition(), collider->GetScale());
		Rectangle targetRect(targetPosition, target->GetScale());
		float prevPositionY = object->GetRigidbody()->GetCurrentVelocity().y * TimeManager::GetInstance().GetFixedDeletaTime();

		if (rect.topPosition > targetRect.bottomPosition - prevPositionY)
		{

			object->GetRigidbody()->SetGround(true);
			object->SetPosition({ targetPosition.x , rect.topPosition - target->GetScale().y * 0.5f });
		}
	}
}

void WallCollisionObject::OnCollisionStay(Collider * target)
{
	if (target->GetColliderLayer() == ColliderLayer::Player || target->GetColliderLayer() == ColliderLayer::Enemy)
	{
		GameObject* object = target->GetOwner();
		Rigidbody* targetRigidbody = target->GetOwner()->GetRigidbody();

		Rectangle rect(collider->GetPosition(), collider->GetScale());
		Rectangle targetRect(target->GetPosition(), target->GetScale());
		
		if (rect.topPosition == targetRect.bottomPosition)
		{
			if (rect.leftPosition > targetRect.leftPosition && rect.leftPosition < targetRect.rightPosition)
				targetRigidbody->SetVelocity({ 0.f, targetRigidbody->GetCurrentVelocity().y });
			else if (rect.rightPosition < targetRect.rightPosition && rect.rightPosition >(targetRect.leftPosition))
				targetRigidbody->SetVelocity({ 0.f, targetRigidbody->GetCurrentVelocity().y });
		}
		else
		{

 			if (rect.bottomPosition > targetRect.topPosition)
			{
				if (rect.leftPosition > targetRect.leftPosition &&  rect.leftPosition < targetRect.rightPosition)
				{
					object->SetPosition({ rect.leftPosition - target->GetScale().x * 0.5f, object->GetPosition().y });
					targetRigidbody->SetVelocity({ 0.f, targetRigidbody->GetCurrentVelocity().y });
				}
				else if (rect.rightPosition < targetRect.rightPosition && rect.rightPosition > targetRect.leftPosition)
				{
					object->SetPosition({ rect.rightPosition + target->GetScale().x * 0.5f, object->GetPosition().y });
					targetRigidbody->SetVelocity({ 0.f, targetRigidbody->GetCurrentVelocity().y });
				}
				else if (rect.rightPosition > targetRect.rightPosition && rect.leftPosition < targetRect.leftPosition
					&& rect.topPosition < targetRect.bottomPosition && !object->GetRigidbody()->IsGround())
				{
					object->GetRigidbody()->SetGround(true);
					object->SetPosition({ target->GetPosition().x , rect.topPosition - target->GetScale().y * 0.5f });
				}
			}
			
		}

	}

}

void WallCollisionObject::OnCollisionEnd(Collider* target)
{
}

bool WallCollisionObject::Save() const
{
    return false;
}

bool WallCollisionObject::Load()
{
    return false;
}

bool WallCollisionObject::SaveCsv(const std::string& filePath) const
{
    return false;
}

bool WallCollisionObject::LoadCsv(const std::string& filePath)
{
    return false;
}

WallCollisionSaveData WallCollisionObject::GetWallCollisionSaveData() const
{
    return WallCollisionSaveData({GetGameObjectSaveData()});
}

void WallCollisionObject::LoadWallCollisionSaveData(const WallCollisionSaveData& data)
{
    LoadGameObjectData(data.gameObjectSaveData);
}
