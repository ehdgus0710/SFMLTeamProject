#pragma once
#include "Enemy.h"

class KoopaTroopa : public Enemy
{
public:
	void Awake() override;
	void Start() override;

	void OnCollisionEnter(Collider* target);
	void OnCollisionStay(Collider* target);
	void OnCollisionEnd(Collider* target);
public:
	KoopaTroopa(const std::string& name = "KoopaTroopa");
	virtual ~KoopaTroopa();
};

