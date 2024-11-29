#pragma once

#include "ReianaBaseState.h"

class ReianaThreeSwordState : public ReianaBaseState
{
public:
	enum class Pos
	{
		NONE,
		POS1,
		POS2,
		POS3,
	};
protected:
	float delayTime;
	float currentDelay;
	sf::Vector2f plusPos1 = { -200.f,-10.f };
	sf::Vector2f plusPos2 = { -160.f,-120.f };
	sf::Vector2f plusPos3 = { -50.f , -200.f };
	int count = 1;

	bool fix;
public:
	void Awake() override;
	void Start() override;

	void CreateKnife();

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
	void LateUpdate(float deltaTime) override;
public:
	ReianaThreeSwordState(ReianaFsm* fsm);
	~ReianaThreeSwordState();
};