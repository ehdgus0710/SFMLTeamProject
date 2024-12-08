#include "stdafx.h"
#include "YggdrasilEnergyBallSmall.h"

#include "Rigidbody.h"
#include "Animator.h"
#include "Collider.h"
#include "Animation.h"

#include "Player.h"

YggdrasilEnergyBallSmall::YggdrasilEnergyBallSmall(GameObject* owner, ColliderLayer thisLayerType, ColliderLayer targetLayer, const std::string& texId, const std::string& name)
	: AnimationBullet(owner, thisLayerType, targetLayer, texId, name)
{

	Animation* animation = new Animation("animations/Enemy/yggdrasil/Effects/EnergyBomb.csv");
	animator->AddAnimation(animation, "EnergyBomb");
	animator->ChangeAnimation("EnergyBomb", true);
}

YggdrasilEnergyBallSmall::~YggdrasilEnergyBallSmall()
{
}
void YggdrasilEnergyBallSmall::OnCollisionEnter(Collider* target)
{
	if (target->GetColliderLayer() == ColliderLayer::Wall)
	{
		lastPos = position;
		OnDestory();
		AnimationGameObject* effect = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new AnimationGameObject("AttackEffect"), LayerType::Effect);
		Animation* animation(new Animation("animations/Enemy/Yggdrasil/Effects/P2EnergyCorpsExplosion.csv"));
		effect->GetAnimator()->AddAnimation(animation, "P2EnergyCorpsExplosion");
		effect->GetAnimator()->ChangeAnimation("P2EnergyCorpsExplosion");
		animation->SetAnimationEndEvent(std::bind(&GameObject::OnDestory, this), animation->GetEndFrameCount());
		effect->SetPosition({ lastPos.x,lastPos.y + 40 });
		effect->SetOrigin(Origins::BottomCenter);
		effect->SetScale({ 3.f,3.f });

		effect->Awake();
		effect->Start();
	}
	else
		AnimationBullet::OnCollisionEnter(target);
}