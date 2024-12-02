#pragma once
#include "AnimationGameObject.h"
#include "YggdrasilFSM.h"


class Rigidbody;
class Player;

class YggdrasilEnergyBallSmall : public AnimationGameObject
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

	void SetAniEnergyBallSmall(std::string name, bool loop);

	void SetYggdrasil(Yggdrasil* yggdrasil);
	void SetPlayer(Player* player);


public:
	YggdrasilEnergyBallSmall(const std::string& name = "YggdrasilEnergyBallSmall");
	virtual ~YggdrasilEnergyBallSmall();
	YggdrasilEnergyBallSmall& operator= (const YggdrasilEnergyBallSmall& other) = delete;
};

