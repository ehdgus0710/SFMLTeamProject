#include "stdafx.h"
#include "AnimationHitBox.h"
#include "Animator.h"
#include "Collider.h"

AnimationHitBox::AnimationHitBox(GameObject* owner, ColliderLayer thisLayerType, ColliderLayer targetLayer, const std::string& texId, const std::string& name)
	: HitBoxObject(owner, thisLayerType, targetLayer, name)
{
	CreateAnimator();
}

void AnimationHitBox::Start()
{
	SetScale(scale);
	SetPosition(position);
	SetRotation(rotation);

	SetOrigin(originPreset);
	animator->Start();
	collider->Reset();
}

void AnimationHitBox::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;
	collider->SetOwnerScale(scale);
}

void AnimationHitBox::SetRotation(float angle)
{
	rotation = angle;
	sprite.setRotation(rotation);
	collider->SetRotation(rotation);
}

void AnimationHitBox::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	sprite.setPosition(position);
	collider->SetPosition(pos);
}

void AnimationHitBox::SetOrigin(Origins preset)
{
	originPreset = preset;
	origin = Utils::SetOrigin(sprite, preset);
	collider->SetOrigin(preset);
}

void AnimationHitBox::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	sprite.setOrigin(origin);
	collider->SetOrigin(newOrigin);
}

void AnimationHitBox::Update(const float& deltaTime)
{
	animator->Update(deltaTime);

	HitBoxObject::Update(deltaTime);
}

void AnimationHitBox::Render(sf::RenderWindow& renderWindow)
{
	renderWindow.draw(sprite);
	collider->Render(renderWindow);
}

void AnimationHitBox::CreateAnimator()
{
	if (animator == nullptr)
		animator = new Animator(this, sprite);
}
