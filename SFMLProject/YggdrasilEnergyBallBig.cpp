#include "stdafx.h"
#include "YggdrasilEnergyBallBig.h"

#include "Rigidbody.h"
#include "Animator.h"
#include "Collider.h"
#include "Animation.h"

#include "Player.h"

YggdrasilEnergyBallBig::YggdrasilEnergyBallBig(GameObject* owner, ColliderLayer thisLayerType, ColliderLayer targetLayer, const std::string& texId, const std::string& name)
	: AnimationBullet(owner, thisLayerType, targetLayer, texId, name)
	, player(nullptr)
{

	Animation* animation = new Animation("animations/Enemy/yggdrasil/Effects/EnergyBomb.csv");
	animator->AddAnimation(animation, "EnergyBomb");
	animator->ChangeAnimation("EnergyBomb", true);
}


YggdrasilEnergyBallBig::~YggdrasilEnergyBallBig()
{
}


void YggdrasilEnergyBallBig::Awake()
{
	AnimationBullet::Awake();
}

void YggdrasilEnergyBallBig::Start()
{
	AnimationBullet::Start();
}

void YggdrasilEnergyBallBig::OnCollisionEnter(Collider* target)
{
	if (target->GetColliderLayer() == ColliderLayer::Wall)
	{
		OnDestory();
	}
	else
		AnimationBullet::OnCollisionEnter(target);
}
void YggdrasilEnergyBallBig::SetYggdrasil(Yggdrasil* yggdrasil)
{
}

void YggdrasilEnergyBallBig::SetPlayer(Player* player)
{
	this->player = player;
}

