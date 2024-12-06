#include "stdafx.h"
#include "AwakeDemensionWaitEffect.h"

#include "Animation.h"
#include "Animator.h"
#include "AnimationHitBox.h"
#include "Collider.h"
#include "AwakeGroundDimention.h"

AwakeDemensionWaitEffect::AwakeDemensionWaitEffect(const std::string& name)
	: AnimationGameObject("AwakeDemensionWaitEffect")
{
	Animation* animation = new Animation("animations/Enemy/Rayanna/Effects/AwakeDemensionWaitEffect.csv");
	animator->AddAnimation(animation, "AwakeDemensionWaitEffect");
	SetScale({ 5.f,2.f });
	randomPos = { (float)Utils::RandomRange(500, 1500), (float)Utils::RandomRange(-300, -100) };
	SetPosition(randomPos);
	SetRotation(Utils::RandomRange(1, 180));
}

void AwakeDemensionWaitEffect::Start()
{
	AnimationGameObject::Start();
	animator->ChangeAnimation("AwakeDemensionWaitEffect");
}

void AwakeDemensionWaitEffect::ChangeAttackAnimation()
{
	this->OnDestory();
	changePos = GetPosition();
	changeRot = GetRotation();
	AwakeGroundDimention* awakeGroundDimention = SCENE_MANAGER.GetCurrentScene()->AddGameObject(new AwakeGroundDimention(), LayerType::EnemyBullet);
	awakeGroundDimention->Start();
	awakeGroundDimention->SetPosition(changePos);
	awakeGroundDimention->SetRotation(changeRot);
	awakeGroundDimention->OnAttack();
}
