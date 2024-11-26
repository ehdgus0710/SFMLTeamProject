#pragma once
#include "Enemy.h"
#include "GoombaFSM.h"
class Goomba : public Enemy
{
public:
	void Awake() override;
	void Start() override;

	void OnCollisionEnter(Collider* target);
	void OnCollisionStay(Collider* target);
	void OnCollisionEnd(Collider* target);
public:
	Goomba(const std::string& name = "Goomba");
	virtual ~Goomba();
};

