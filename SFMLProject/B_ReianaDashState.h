#pragma once

#include "B_ReianaBaseState.h"

class B_ReianaDashState : public B_ReianaBaseState
{
protected:
	sf::Vector2f startPosition;
	sf::Vector2f endPosition;
	sf::Vector2f movePosition;
	sf::Vector2f B_ReianaPos;
	sf::Vector2f cameraFixPos;

	float ySpeed = 400.f;
	float xSpeed = 2000.f;
	float currentWaitTime = 0.f;

private:
	void BackStap(float deltaTime);

public:
	void Awake() override;
	void Start() override;

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
	void LateUpdate(float deltaTime) override;
public:
	B_ReianaDashState(B_ReianaFsm* fsm);
	~B_ReianaDashState();
};
