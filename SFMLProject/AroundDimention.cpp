#include "stdafx.h"
#include "AroundDimention.h"
#include "AnimationHitBox.h"

void AroundDimention::CreateAnimator()
{
}

AroundDimention::AroundDimention(GameObject* owner, ColliderLayer thisLayerType, ColliderLayer targetLayer, const std::string& texId, const std::string& name)
	: AnimationHitBox(owner, thisLayerType, targetLayer, texId, name)
{
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
