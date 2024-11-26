#pragma once

#include "FSMController.h"

class Player;

class PlayerFSM : public FSMController<PlayerStateType>
{
protected:
	Player* owner;

private:
	void CreateAllState();

public:
	BaseState<PlayerStateType>* CreateState(PlayerStateType type);
	Player* GetPlayer() { return owner; }

public:
	void Awake() override;
	void Start() override; 

	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
	void LateUpdate(float deltaTime) override;

public:
	PlayerFSM(Player* owner);
	virtual  ~PlayerFSM();
};

