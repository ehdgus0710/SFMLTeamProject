#pragma once

#include "B_ReianaBaseState.h"

class B_ReianaBackStap : public B_ReianaBaseState
{
protected:
	sf::Vector2f startPosition;
	sf::Vector2f endPosition;

	float currentTime = 0.f;
	float time = 0.3f;

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
	B_ReianaBackStap(B_ReianaFsm* fsm);
	~B_ReianaBackStap();
};

