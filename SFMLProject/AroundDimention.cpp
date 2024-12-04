#include "stdafx.h"

#include "Animation.h"
#include "Animator.h"
#include "AroundDimention.h"
#include "AnimationHitBox.h"

void AroundDimention::CreateAnimator()
{
}

AroundDimention::AroundDimention(GameObject* owner, ColliderLayer thisLayerType, ColliderLayer targetLayer, const std::string& texId, const std::string& name)
	: AnimationHitBox(owner, thisLayerType, targetLayer, texId, name)
{
	Animation* animation = new Animation("animations/Enemy/Rayanna/Effects/DimensionPierce.csv");
	animator->AddAnimation(animation, "DimensionPierce");
	
}

void AroundDimention::Start()
{
	AnimationHitBox::Start();
}

void AroundDimention::Update(const float& deltaTime)
{
}

void AroundDimention::Render(sf::RenderWindow& renderWindow)
{
}
