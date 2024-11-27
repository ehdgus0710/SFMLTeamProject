#pragma once

#include "FSMController.h"

class Chimera;

class ChimeraFSM : public FSMController<ChimeraStateType>
{
protected:
	Chimera* owner;

private:
	void CreateAllState();

public:
	BaseState<ChimeraStateType>* CreateState(ChimeraStateType type);
	Chimera* GetChimera() { return owner; }

public:
	void Awake() override;
	void Start() override;

	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
	void LateUpdate(float deltaTime) override;

public:
	ChimeraFSM(Chimera* owner);
	virtual  ~ChimeraFSM();
};

