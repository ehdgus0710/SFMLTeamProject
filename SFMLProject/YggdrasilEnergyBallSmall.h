#pragma once
#include "AnimationBullet.h"
#include "YggdrasilFSM.h"

class YggdrasilEnergyBallSmall : public AnimationBullet
{
public:
	YggdrasilEnergyBallSmall(GameObject* owner, ColliderLayer thisLayerType, ColliderLayer targetLayer, const std::string& texId, const std::string& name = "YggdrasilEnergyBallSmall");
	virtual ~YggdrasilEnergyBallSmall();
	YggdrasilEnergyBallSmall& operator= (const YggdrasilEnergyBallSmall& other) = delete;
};

