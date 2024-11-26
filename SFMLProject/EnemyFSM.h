#pragma once
#include "FSMController.h"

class Enemy;
class EnemyFSM : public FSMController<EnemyStateType>
{
protected:
	Enemy*			owner;

protected:
	virtual void CreateAllState();

public:
	BaseState<EnemyStateType>* CreateState(EnemyStateType type) override;
	Enemy* GetEnemy() { return owner; }

public:
	void Awake() override;
	void Start() override;

	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
	void LateUpdate(float deltaTime) override;

public:
	EnemyFSM(Enemy* owner);
	virtual  ~EnemyFSM();

};

