#include "stdafx.h"
#include "RisingReady.h"

#include "Collider.h"
#include "Animation.h"
#include "Animator.h"
#include "Enemy.h"
#include "Rigidbody.h"
#include "HitBoxObject.h"
#include "Scene.h"
#include "Reiana.h"

RisingReady::RisingReady(GameObject* owner, ColliderLayer thisLayerType, ColliderLayer targetLayer, const std::string& texId, const std::string& name)
	: AnimationBullet(owner, thisLayerType, targetLayer, texId, name)
	, reiana(nullptr)
{
}

void RisingReady::Start()
{
	reiana = dynamic_cast<Reiana*>(SCENE_MANAGER.GetCurrentScene()->FindGameObject("Reiana"));

	AnimationBullet::Start();

	effect1 = SCENE_MANAGER.GetCurrentScene()->AddGameObject(new AnimationGameObject("AwakenedThunder"), LayerType::EnemyBullet);
	Animation* animation = new Animation();
	animation = new Animation();
	animation->loadFromFile("animations/Enemy/Rayanna/Effects/RisingPierceReady.csv");
	effect1->GetAnimator()->AddAnimation(animation, "RisingPierceReady");
	effect1->GetAnimator()->ChangeAnimation("RisingPierceReady");
	sf::Vector2f reianaPos = { reiana->GetPosition().x,reiana->GetPosition().y +60};
	effect1->SetPosition(reianaPos + (reiana->IsFlipX() ? risingReadyPos : -risingReadyPos));
	effect1->Awake();
	effect1->Start();
	animation->SetAnimationEndEvent(std::bind(&GameObject::OnDestory, effect1), animation->GetFrameCount() - 1);
	effect1->SetOrigin(Origins::BottomCenter);
	effect1->SetScale({ 3.f,3.f });
}
void RisingReady::Update(const float& deltaTime)
{

	AnimationBullet::Update(deltaTime);
}

sf::Vector2f RisingReady::GetEffectPos()
{
	return effect1->GetPosition();
}

void RisingReady::setDelay(float delay)
{
	delayTime = delay;
}