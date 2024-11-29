#pragma once

#include "ReianaBaseState.h"

class ReianaBackStap : public ReianaBaseState
{
protected:
	sf::Vector2f startPosition;
	sf::Vector2f endPosition;

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
	ReianaBackStap(ReianaFsm* fsm);
	~ReianaBackStap();
};

