#include "stdafx.h"
#include "AnimationGameObject.h"

#include "Animator.h"
#include "Collider.h"


AnimationGameObject::AnimationGameObject(const std::string& name)
	: GameObject(name)
	, isFlipX(false)
{
}

AnimationGameObject::~AnimationGameObject()
{
}


void AnimationGameObject::Awake()
{
}

void AnimationGameObject::Start()
{
	SetScale(scale);
	SetPosition(position);
	SetRotation(rotation);

	SetOrigin(originPreset);
	animator->Start();

	if(collider != nullptr)
		collider->Reset();
}

void AnimationGameObject::Update(const float& deltaTime)
{
}

void AnimationGameObject::FixedUpdate(const float& deltaTime)
{
}

void AnimationGameObject::LateUpdate(const float& deltaTime)
{
}

void AnimationGameObject::Render(sf::RenderWindow& renderWindow)
{
	animator->Render(renderWindow);

	if (collider != nullptr)
		collider->Render(renderWindow);
}

void AnimationGameObject::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	sprite.setPosition(pos);
	if (collider != nullptr)
		collider->SetPosition(pos);
}

void AnimationGameObject::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;

	animator->SetScale(scale);
	if (collider != nullptr)
		collider->SetOwnerScale(scale);
}

void AnimationGameObject::SetRotation(float angle)
{
	rotation = angle;
	sprite.rotate(angle);
	collider->SetRotation(angle);
}

void AnimationGameObject::SetOrigin(Origins preset)
{
	originPreset = preset;
	origin = Utils::SetOrigin(sprite, preset);
	if (collider != nullptr)
		collider->SetOrigin(preset);
}

void AnimationGameObject::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	sprite.setOrigin(origin);
	if (collider != nullptr)
		collider->SetOrigin(newOrigin);
}

void AnimationGameObject::OnFlipX()
{
	isFlipX = !isFlipX;

	scale.x *= -1.f;
	SetScale(scale);
}

void AnimationGameObject::CreateAnimator()
{
	if (animator != nullptr)
		return;

	animator = new Animator(this, sprite);
}

sf::FloatRect AnimationGameObject::GetLocalBounds() const
{
	return sprite.getLocalBounds();
}

sf::FloatRect AnimationGameObject::GetGlobalBounds() const
{
	return sprite.getGlobalBounds();
}