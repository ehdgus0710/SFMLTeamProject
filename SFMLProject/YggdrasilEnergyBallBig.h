#pragma once

#include "AnimationGameObject.h"
#include "YggdrasilFSM.h"
class Rigidbody;
class Player;

class YggdrasilEnergyBallBig : public AnimationGameObject
{
protected:
	Player* player;

public:
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void FixedUpdate(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;

	void OnCollisionEnter(Collider* target) override;
	void OnCollisionStay(Collider* target) override;
	void OnCollisionEnd(Collider* target) override;

	void fire();

	void SetAniEnergyBallBig(std::string name, bool loop);

	void SetYggdrasil(Yggdrasil* yggdrasil);
	void SetPlayer(Player* player);


public:
	YggdrasilEnergyBallBig(const std::string& name = "YggdrasilEnergyBallBig");
	virtual ~YggdrasilEnergyBallBig();
	YggdrasilEnergyBallBig& operator= (const YggdrasilEnergyBallBig& other) = delete;
};
