#include "stdafx.h"
#include "BrickBlockParticle.h"
#include "Rigidbody.h"

BrickBlockParticle::BrickBlockParticle(const sf::IntRect& rect, const std::string& texId, const std::string& name)
	: SpriteGameObject(texId, name)
	, textureRect(rect)
	, rotationSpeed(5.f)
{
	rigidBody = new Rigidbody(this);
	rigidBody->SetGround(false);
}

void BrickBlockParticle::StartMove(float height)
{
	rigidBody->SetGround(false);
	rigidBody->SetVelocity({ 200.f * moveDirection.x, height });
}

void BrickBlockParticle::Start()
{
	scale = { 4.f, 4.f };
	sprite.setTexture(ResourcesManager<sf::Texture>::GetInstance().Get(textureId));
	sprite.setTextureRect(textureRect);
	SetOrigin(Origins::MiddleCenter);
	SetScale(scale);
	SetPosition(position);
	SetRotation(rotation);
}

void BrickBlockParticle::Update(const float& deltaTime)
{
	if (rigidBody->GetCurrentVelocity().y > 0.f)
	{
		SetRotation(rotation + rotationSpeed * moveDirection.x);
	}

	if (position.y >= 2000.f)
		OnDestory();
}

void BrickBlockParticle::FixedUpdate(const float& deltaTime)
{
	rigidBody->SetVelocity({ 200.f * moveDirection.x, rigidBody->GetCurrentVelocity().y});
	rigidBody->FixedUpdate(deltaTime);
}
