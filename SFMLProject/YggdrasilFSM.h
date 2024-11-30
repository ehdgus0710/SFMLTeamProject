#pragma once
#include "FSMController.h"

class Yggdrasil;

class YggdrasilFSM : public FSMController<YggdrasilStateType>
{
protected:
	Yggdrasil* owner;

private:
	void CreateAllState();

public:
	BaseState<YggdrasilStateType>* CreateState(YggdrasilStateType type);
	Yggdrasil* GetChimera() { return owner; }

public:
	void Awake() override;
	void Start() override;

	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
	void LateUpdate(float deltaTime) override;

public:
	YggdrasilFSM(Yggdrasil* owner);
	virtual  ~YggdrasilFSM();
};

