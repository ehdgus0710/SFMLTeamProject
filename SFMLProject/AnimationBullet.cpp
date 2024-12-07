#include "stdafx.h"
#include "AnimationBullet.h"
#include "Animator.h"
#include "Collider.h"

AnimationBullet::AnimationBullet(GameObject* owner, ColliderLayer thisLayerType, ColliderLayer targetLayer, const std::string& texId, const std::string& name)
	: Bullet(owner, thisLayerType, targetLayer, texId, name)
{
	CreateAnimator();
}

AnimationBullet::AnimationBullet(GameObject* owner, ColliderLayer thisLayerType, ColliderLayerMask targetLayerMask, const std::string& texId, const std::string& name)
	: Bullet(owner, thisLayerType, targetLayer, texId, name)
{
	CreateAnimator();
}
void AnimationBullet::Start()
{
	SetScale(scale);
	SetPosition(position);
	SetRotation(rotation);

	SetOrigin(originPreset);
	animator->Start();
	collider->Reset();
	// collider->SetScale({ (sf::Vector2f)animator->GetCurrentAnimation()->GetFrameInfo()[0].rectSize });
}

void AnimationBullet::Render(sf::RenderWindow& renderWindow)
{
	renderWindow.draw(sprite);
	collider->Render(renderWindow);
}