#pragma once

#include "FSMController.h"

class Reiana;

class ReianaFsm : public FSMController<ReianaStateType>
{
protected:
	Reiana* owner;

private:
	void CreateAllState();

public:
	BaseState<ReianaStateType>* CreateState(ReianaStateType type);
	Reiana* GetChimera() { return owner; }

public:
	void Awake() override;
	void Start() override;

	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
	void LateUpdate(float deltaTime) override;

public:
	ReianaFsm(Reiana* owner);
	virtual  ~ReianaFsm();
};

