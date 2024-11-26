#pragma once
#include "EnemyFSM.h"

class KoopaFSM : public EnemyFSM
{
protected:
	void CreateAllState() override;

public:
	void Awake() override;
	void Start() override;

	BaseState<EnemyStateType>* CreateState(EnemyStateType type) override;
public:
	KoopaFSM(Enemy* owner);
	virtual  ~KoopaFSM();
};