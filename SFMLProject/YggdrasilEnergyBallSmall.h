#pragma once
#include "AnimationBullet.h"
#include "YggdrasilFSM.h"

class YggdrasilEnergyBallSmall : public AnimationBullet
{
protected:
	sf::Vector2f lastPos;
public:
	YggdrasilEnergyBallSmall(GameObject* owner, ColliderLayer thisLayerType, ColliderLayer targetLayer, const std::string& texId, const std::string& name = "YggdrasilEnergyBallSmall");
	virtual ~YggdrasilEnergyBallSmall();
	void OnCollisionEnter(Collider* target);
	YggdrasilEnergyBallSmall& operator= (const YggdrasilEnergyBallSmall& other) = delete;
};

