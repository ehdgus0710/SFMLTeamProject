#include "stdafx.h"
#include "ScaffoldingObject.h"

#include "Collider.h"
#include "Collision.h"

#include "Rigidbody.h"
#include "Player.h"
#include "Enemy.h"

ScaffoldingObject::ScaffoldingObject(const std::string& texId, const std::string& name)
	: SpriteGameObject(texId, name)
{
	CreateCollider(ColliderType::Rectangle, ColliderLayer::Scaffolding);
}

void ScaffoldingObject::OnCollisionEnter(Collider* target)
{
	if (target->GetColliderLayer() == ColliderLayer::Player || target->GetColliderLayer() == ColliderLayer::Enemy)
	{
		GameObject* object = target->GetOwner();
		sf::Vector2f targetPosition = target->GetPosition();

		Rectangle rect(collider->GetPosition(), collider->GetScale());
		Rectangle targetRect(targetPosition, target->GetScale());
		float prevPositionY = object->GetRigidbody()->GetPrevDropSpeed();

		if (rect.topPosition > targetRect.bottomPosition - prevPositionY)
		{
			object->GetRigidbody()->SetGround(true);
			object->SetPosition(sf::Vector2f{ targetPosition.x , rect.topPosition - target->GetScale().y * 0.5f } - target->GetOffsetPosition());
		}
	}
}