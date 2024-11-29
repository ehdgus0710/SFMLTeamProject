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
