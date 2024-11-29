#pragma once

#include "AnimationGameObject.h"
#include "YggdrasilFSM.h"
class Rigidbody;
class Player;

class YggdrasilHead : public AnimationGameObject
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

	void SetYggdrasil(Yggdrasil* player);
	void SetPlayer(Player* player);


public:
	YggdrasilHead(const std::string& name = "YggdrasilHead");
	virtual ~YggdrasilHead();
	YggdrasilHead& operator= (const YggdrasilHead& other) = delete;
};

