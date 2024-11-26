#pragma once
#include "EnemyBaseState.h"

class KoopaAttackState : public EnemyBaseState
{
private:
	Rigidbody*		rigidbody;
	sf::Vector2f	createPosition;

private:
	void StartAttack();
	void EndAttack();
public:
	void Awake() override;
	void Start() override;

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
	void LateUpdate(float deltaTime) override;
public:
	KoopaAttackState(EnemyFSM* fsm);
	~KoopaAttackState();
};

