#pragma once

#include "EnemyFSM.h"

class GoombaFSM : public EnemyFSM
{
protected:
	void CreateAllState() override;

public:
	void Awake() override;
	void Start() override;

	BaseState<EnemyStateType>* CreateState(EnemyStateType type) override;
public:
	GoombaFSM(Enemy* owner);
	virtual  ~GoombaFSM();
};

