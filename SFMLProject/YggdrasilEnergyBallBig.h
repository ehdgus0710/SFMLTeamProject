#pragma once

#include "AnimationBullet.h"
#include "YggdrasilFSM.h"
class Player;

class YggdrasilEnergyBallBig : public AnimationBullet
{
protected:
	Player* player;
	sf::Vector2f lastPos;

public:
	void Awake() override;
	void Start() override;

	void Update(const float& deltaTime) override;
	void OnCollisionEnter(Collider* target) override;
	void SetYggdrasil(Yggdrasil* yggdrasil);
	void SetPlayer(Player* player);


public:
	YggdrasilEnergyBallBig(GameObject* owner, ColliderLayer thisLayerType, ColliderLayer targetLayer, const std::string& texId, const std::string& name = "YggdrasilEnergyBallBig");
	virtual ~YggdrasilEnergyBallBig();
	YggdrasilEnergyBallBig& operator= (const YggdrasilEnergyBallBig& other) = delete;
};
