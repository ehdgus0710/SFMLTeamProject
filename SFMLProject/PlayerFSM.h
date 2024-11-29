#pragma once

#include "FSMController.h"

class Player;
class Head;
class PlayerBaseState;

class PlayerFSM : public FSMController<PlayerStateType>
{
protected:
	Player* owner;
	Head*	head;

private:
	void CreateAllState();

public:
	BaseState<PlayerStateType>* CreateState(PlayerStateType type);
	PlayerBaseState* GetCurrentState();
	Player* GetPlayer() { return owner; }

public:
	void Awake() override;
	void Start() override; 

	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
	void LateUpdate(float deltaTime) override;

public:
	PlayerFSM(Player* owner);
	PlayerFSM(Head* owner);
	virtual  ~PlayerFSM();
};

