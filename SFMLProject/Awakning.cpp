#include "stdafx.h"
#include "Awakning.h"

#include "Animation.h"
#include "Animator.h"
#include "AnimationHitBox.h"
#include "Collider.h"
#include "Camera.h"

Awakning::Awakning(const std::string& name)
	: AnimationGameObject("AwakenNing")
{
	SoundManger::GetInstance().StopBgm();
	SoundManger::GetInstance().PlaySfx("Leiana_Awakening", false);
	SCENE_MANAGER.GetCurrentScene()->GetMainCamera()->SetCameraShake({ 10.f,10.f }, MoveDirection::Random, 100.f, 3.f);
	Animation* animation = new Animation("animations/Enemy/Rayanna/Effects/AwakenNing.csv");
	animator->AddAnimation(animation, "AwakenNing");
	SetScale({ 4.f,4.f });
	animator->SetAnimationSpeed(2.f);
	SetOrigin(Origins::BottomCenter);
	animation->SetAnimationEndEvent(std::bind(&GameObject::OnDestory, this), animation->GetEndFrameCount());
}

void Awakning::Start()
{
	AnimationGameObject::Start();
	animator->ChangeAnimation("AwakenNing");
}