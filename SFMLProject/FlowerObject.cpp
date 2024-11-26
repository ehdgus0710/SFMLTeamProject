#include "stdafx.h"
#include "FlowerObject.h"
#include "Animator.h"
#include "Collider.h"
#include "Animation.h"
#include "Rigidbody.h"

FlowerObject::FlowerObject()
	: ItemObject(ItemType::Flower, "Items", "Flower")
{
	CreateAnimator();
	rigidBody = new Rigidbody(this);
	animator->LoadCsv("animators/flower.csv");
}

void FlowerObject::Start()
{
	SetScale(scale);
	SetPosition(position);
	SetRotation(rotation);

	SetOrigin(originPreset);
	animator->Start();
	collider->Reset();
	collider->SetScale({ (sf::Vector2f)animator->GetCurrentAnimation()->GetFrameInfo()[0].rectSize });
	animator->ChangeAnimation("flower", true);
}

void FlowerObject::Update(const float& deltaTime)
{
	animator->Update(deltaTime);
	ItemObject::Update(deltaTime);
}

void FlowerObject::CreateAnimator()
{
	if (animator == nullptr)
		animator = new Animator(this, sprite);
}
