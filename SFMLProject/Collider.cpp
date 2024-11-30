#include "stdafx.h"
#include "Collider.h"
#include "CollisionRectangle.h"
#include "CollisionPoint.h"
#include "CollisionCircle.h"

int Collider::globalCount = 0;

bool Collider::isRender = true;

Collider::Collider(ColliderType colliderType, ColliderLayer colliderLayer, sf::Vector2f offset, sf::Vector2f size)
	: active(true)
	, collision(nullptr)
	, colliderLayer(colliderLayer)
	, collisionCount(0)
	, iD(globalCount++)
	, isDestory(false)
	, colliderScale(size)
	, ownerScale(sf::Vector2f::one)
{
	CreateCollision(colliderType, offset, size);
}

Collider::Collider(const Collider& other)
	: active(true)
	, colliderLayer(colliderLayer)
	, collisionCount(0)
	, iD(globalCount++)
	, isDestory(false)
	, owner(nullptr)
	, colliderRotation(0.f)
{
	ColliderType colliderType = other.collision->GetColliderType();
	if (ColliderType::Rectangle == colliderType)
		collision = new CollisionRectangle(other.colliderScale);
	else if (ColliderType::Circle == colliderType)
		collision = new CollisionCircle(other.colliderScale.x);
	else
		collision = new CollisionPoint();

	offsetPosition = other.offsetPosition;
	ColliderManager::GetInstance().AddCollider(this, colliderLayer);
}

Collider::~Collider()
{
	if (collision != nullptr)
		delete collision;
}

void Collider::OnDestory()
{
	isDestory = true;
	SetActive(false);
	ColliderManager::GetInstance().SetDestoryCollider(this);
}

bool Collider::IsDestory()
{
	return isDestory;
}

void Collider::SetOffsetPosition(const sf::Vector2f& offset)
{
	offsetPosition = offset;
	collision->SetPosition(position + offsetPosition);
}

void Collider::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	collision->SetPosition(position + offsetPosition);
}

void Collider::SetOrigin(const sf::Vector2f& origin)
{
	collision->SetOrigin(origin);
}

void Collider::SetOrigin(const Origins& origins)
{
	collision->SetOrigin(origins);
}

Origins Collider::GetOrigins()
{
	return collision->GetOrigins();
} 

sf::Vector2f Collider::GetOrigin()
{
	return collision->GetOrigin();
}

sf::FloatRect Collider::GetLocalBounds()
{
	return collision->GetLocalBounds();
}

sf::FloatRect Collider::GetGlobalBounds()
{
	return collision->GetGlobalBounds();
}

sf::Vector2f Collider::GetRealPosition() const
{
	return collision->GetRealPosition();
}

sf::Vector2f Collider::GetPosition()
{
	return collision->GetPosition();
}

sf::Vector2f Collider::GetScale()
{
	return collision->GetScale();
}

void Collider::SetOwnerScale(const sf::Vector2f& size)
{
	ownerScale = size;
	ownerScale = { abs(ownerScale.x), abs(ownerScale.y) };
	SetScale(colliderScale);
}

void Collider::SetRotation(float angle)
{
	colliderRotation = angle;
	collision->SetRotation(angle);
}

float Collider::GetRotation()
{
	return collision->GetRotation();
}

void Collider::SetScale(const sf::Vector2f& size)
{
	colliderScale = size;
	collision->SetScale(size * ownerScale);
}

void Collider::Reset()
{
	collisionTargetVector.clear();
	collision->Reset();
	isDestory = false;
	SetActive(true);
}

void Collider::CreateCollision(ColliderType colliderType, sf::Vector2f offset, sf::Vector2f size)
{
	if (ColliderType::Rectangle == colliderType)
		collision = new CollisionRectangle(size);
	else if (ColliderType::Circle == colliderType)
		collision = new CollisionCircle(size.x);
	else
		collision = new CollisionPoint();

	offsetPosition = offset;
	ColliderManager::GetInstance().AddCollider(this, colliderLayer);
}

void Collider::Render(sf::RenderWindow& renderWindow)
{
	if(active && isRender)
		collision->Render(renderWindow);
}

void Collider::OnCollisionEnter(Collider* target)
{
	collisionTargetVector.push_back(target);
	collision->IsCollision();
	owner->OnCollisionEnter(target);
}

void Collider::OnCollisionStay(Collider* target)
{
	owner->OnCollisionStay(target);
}

void Collider::OnCollisionEnd(Collider* target)
{
	owner->OnCollisionEnd(target);
	collision->EndCollision();
	if(!isDestory)
		collisionTargetVector.erase(std::find(collisionTargetVector.begin(), collisionTargetVector.end(), target));
}

ColliderType Collider::GetColliderType()
{
	return collision->GetColliderType();
}
