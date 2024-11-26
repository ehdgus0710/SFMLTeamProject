#pragma once

#include "EnemyFSM.h"

class KoopaTroopaFSM : public EnemyFSM
{
protected:
	void CreateAllState() override;

public:
	void Awake() override;
	void Start() override;

	BaseState<EnemyStateType>* CreateState(EnemyStateType type) override;
public:
	KoopaTroopaFSM(Enemy* owner);
	virtual  ~KoopaTroopaFSM();
};

