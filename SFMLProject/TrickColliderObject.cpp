#include "stdafx.h"
#include "TrickColliderObject.h"
#include "Collider.h"
#include "Player.h"

int TrickColliderObject::wallID = 0;

TrickColliderObject::TrickColliderObject(const std::string& name)
	: GameObject(name + std::to_string(wallID++))
{
	originPreset = Origins::MiddleCenter;
	CreateCollider(ColliderType::Rectangle, ColliderLayer::Wall);
}

TrickColliderObject::~TrickColliderObject()
{
}

void TrickColliderObject::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;
	collider->SetOwnerScale(scale);
	SetOrigin(originPreset);
}

void TrickColliderObject::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	collider->SetPosition(position);
}

void TrickColliderObject::SetOrigin(Origins preset)
{
	originPreset = preset;
	collider->SetOrigin(preset);
}

sf::FloatRect TrickColliderObject::GetLocalBounds() const
{
	return collider->GetLocalBounds();
}

sf::FloatRect TrickColliderObject::GetGlobalBounds() const
{
	return collider->GetGlobalBounds();
}
void TrickColliderObject::Start()
{
	collider->Reset();
}

void TrickColliderObject::OnCollisionEnter(Collider* target)
{
}

void TrickColliderObject::OnCollisionStay(Collider* target)
{
	if (target->GetColliderLayer() == ColliderLayer::Player)
	{
		Player* player = (Player*)target->GetOwner();
	}
}

void TrickColliderObject::OnCollisionEnd(Collider* target)
{
}

bool TrickColliderObject::Save() const
{
	return false;
}

bool TrickColliderObject::Load()
{
	return false;
}

bool TrickColliderObject::SaveCsv(const std::string& filePath) const
{
	return false;
}

bool TrickColliderObject::LoadCsv(const std::string& filePath)
{
	return false;
}