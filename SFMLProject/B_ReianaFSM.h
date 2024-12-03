#pragma once

#include "FSMController.h"

class B_Reiana;

class B_ReianaFsm : public FSMController<B_ReianaStateType>
{
protected:
	B_Reiana* owner;

private:
	void CreateAllState();

public:
	BaseState<B_ReianaStateType>* CreateState(B_ReianaStateType type);
	B_Reiana* GetChimera() { return owner; }

public:
	void Awake() override;
	void Start() override;

	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
	void LateUpdate(float deltaTime) override;

public:
	B_ReianaFsm(B_Reiana* owner);
	virtual  ~B_ReianaFsm();
};

