#pragma once

#include "ChimeraBaseState.h"

class ChimeraGroundAttackState : public ChimeraBaseState
{
protected:
	sf::Vector2f startPosition;
	sf::Vector2f endPosition;

	sf::Vector2f moveDistance = {500.f,500.f};
	sf::Vector2f saveEndPos;
	sf::Vector2f saveStartPos;


	float moveTime = 2.f;
	float currentTime = 0.f;
	float damage = 20.f;

	bool playComplete = false;

private:
	void StartMove();
	void ReturnMove();

public:
	void Awake() override;
	void Start() override;

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
	void LateUpdate(float deltaTime) override;
public:
	ChimeraGroundAttackState(ChimeraFSM* fsm);
	~ChimeraGroundAttackState();
};

