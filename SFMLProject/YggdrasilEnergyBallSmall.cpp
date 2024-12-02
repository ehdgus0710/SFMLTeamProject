#include "stdafx.h"
#include "YggdrasilEnergyBallSmall.h"
#include "Animator.h"
#include "Animation.h"


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