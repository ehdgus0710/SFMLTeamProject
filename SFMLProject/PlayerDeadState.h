#pragma once

#include "PlayerBaseState.h"
class Head;

class PlayerDeadState : public PlayerBaseState
{
private:

	Head* head;

	/*sf::Vector2f endHeadThrowPosition;
	sf::Vector2f startHeadThrowPosition;*/

	float currentTime;
	float deadStateTime;
	float headRotationTime;

public:
	// void Awake() override;
	// void Start() override;

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
public:
	PlayerDeadState(PlayerFSM* fsm);
	~PlayerDeadState() = default;
};