#pragma once

#include "FSMController.h"

class AwakeReiana;

class AwakeReianaFsm : public FSMController<AwakeReianaStateType>
{
protected:
	AwakeReiana* owner;

private:
	void CreateAllState();

public:
	BaseState<AwakeReianaStateType>* CreateState(AwakeReianaStateType type);
	AwakeReiana* GetChimera() { return owner; }

public:
	void Awake() override;
	void Start() override;

	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
	void LateUpdate(float deltaTime) override;

public:
	AwakeReianaFsm(AwakeReiana* owner);
	virtual  ~AwakeReianaFsm();
};

