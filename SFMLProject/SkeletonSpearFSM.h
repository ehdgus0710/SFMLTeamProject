#pragma once
#include "FSMController.h"

class SkeletonSpear;
class SkeletonSpearBaseState;

class SkeletonSpearFSM : public FSMController<SkeletonSpearStateType>
{
protected:
	SkeletonSpear* owner;

private:
	void CreateAllState();

public:
	BaseState<SkeletonSpearStateType>* CreateState(SkeletonSpearStateType type);
	SkeletonSpearBaseState* GetCurrentState();
	SkeletonSpearBaseState* GetState(SkeletonSpearStateType type);
	SkeletonSpear* GetSkeletonSpear() { return owner; }

public:
	void Awake() override;
	void Start() override;

	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
	void LateUpdate(float deltaTime) override;

public:
	SkeletonSpearFSM(SkeletonSpear* owner);
	virtual  ~SkeletonSpearFSM();
};