#pragma once

#include "AnimationBullet.h"
#include "YggdrasilFSM.h"
class Player;

class YggdrasilEnergyBallBig : public AnimationBullet
{
protected:
	Player* player;

public:
	void Awake() override;
	void Start() override;

	void OnCollisionEnter(Collider* target) override;
	void SetYggdrasil(Yggdrasil* yggdrasil);
	void SetPlayer(Player* player);


public:
	YggdrasilEnergyBallBig(GameObject* owner, ColliderLayer thisLayerType, ColliderLayer targetLayer, const std::string& texId, const std::string& name = "YggdrasilEnergyBallBig");
	virtual ~YggdrasilEnergyBallBig();
	YggdrasilEnergyBallBig& operator= (const YggdrasilEnergyBallBig& other) = delete;
};
