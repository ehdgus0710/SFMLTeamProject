#include "stdafx.h"
#include "HitBoxObject.h"
#include "Collider.h"
#include "Enemy.h"
#include "Player.h"

HitBoxObject::HitBoxObject(GameObject* owner, ColliderLayer thisLayerType,ColliderLayer targetLayerType, const std::string& name)
	: GameObject(name)
	, owner(owner)
	, targetLayer(targetLayer)
	, isOwnerFollow(false)
	, damage(0.f)
	, lifeTime(0.f)
	, currentLifeTime(0.f)
	, useLifeTime(false)
	, hitLayer(0)
{
	CreateCollider(ColliderType::Rectangle, thisLayerType);
}

HitBoxObject::HitBoxObject(GameObject* owner, ColliderLayer thisLayerType, ColliderLayer targetLayer, bool ownerFollow, const sf::Vector2f& offsetPos, const std::string& name)
	: GameObject(name)
	, owner(owner)
	, targetLayer(targetLayer)
	, isOwnerFollow(ownerFollow)
	, offsetPosition(offsetPos)
	, damage(0.f)
	, lifeTime(0.f)
	, currentLifeTime(0.f)
	, useLifeTime(false)
	, hitLayer(0)
{
	CreateCollider(ColliderType::Rectangle, thisLayerType);
}

HitBoxObject::~HitBoxObject()
{
}

void HitBoxObject::OwnerFollow()
{
	if (owner->GetScale().x == -1.f)
		SetPosition(owner->GetPosition() - offsetPosition);
	else
		SetPosition(owner->GetPosition() + offsetPosition);
}

void HitBoxObject::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;
	collider->SetOwnerScale(scale);
}

void HitBoxObject::SetRotation(float angle)
{
	rotation = angle;
	collider->SetRotation(angle);
}

void HitBoxObject::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	collider->SetPosition(pos);
}

void HitBoxObject::SetOrigin(Origins preset)
{
	originPreset = preset;
	collider->SetOrigin(preset);
}

void HitBoxObject::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	collider->SetOrigin(newOrigin);
}

sf::FloatRect HitBoxObject::GetLocalBounds() const
{
    return collider->GetLocalBounds();
}

sf::FloatRect HitBoxObject::GetGlobalBounds() const
{
    return collider->GetGlobalBounds();
}

void HitBoxObject::Awake()
{
}

void HitBoxObject::Start()
{
	SetScale(scale);
	SetPosition(position);
	SetRotation(rotation);

	SetOrigin(originPreset);
	collider->Reset();
}

void HitBoxObject::Release()
{
}

void HitBoxObject::Update(const float& deltaTime)
{
	if (isOwnerFollow)
	{
		OwnerFollow();
	}

	if (useLifeTime)
	{
		currentLifeTime += deltaTime;

		if (currentLifeTime >= lifeTime)
			OnDestory();
	}
}

void HitBoxObject::OnCollisionEnter(Collider* target)
{
	if (target->GetColliderLayer() == targetLayer)
	{
		if (target->GetColliderLayer() == ColliderLayer::Player)
		{
			((Player*)target->GetOwner())->TakeDamage(damage);
		}
		else if (target->GetColliderLayer() == ColliderLayer::Enemy)
		{
			((Enemy*)target->GetOwner())->TakeDamage(damage);
		}

		for (auto& hitEvent : startHitEvents)
		{
			if (hitEvent)
				hitEvent();
		}
	}
}

void HitBoxObject::OnCollisionStay(Collider* target)
{
}

void HitBoxObject::OnCollisionEnd(Collider* target)
{
	if (target->GetColliderLayer() == targetLayer)
	{
		if (target->GetColliderLayer() == ColliderLayer::Player)
		{

		}
		else if (target->GetColliderLayer() == ColliderLayer::Enemy)
		{

		}

		for (auto& hitEvent : endHitEvents)
		{
			if(hitEvent)
				hitEvent();
		}
	}
}

bool HitBoxObject::SaveCsv(const std::string& filePath) const
{
    return false;
}

bool HitBoxObject::LoadCsv(const std::string& filePath)
{
    return false;
}