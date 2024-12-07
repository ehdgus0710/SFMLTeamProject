#pragma once
#include "SkeletonSpearBaseState.h"

class SkeletonSpearSkill1State : public SkeletonSpearBaseState
{
protected:
	Rigidbody* rigidbody;

	sf::Vector2f	dashEndPos;
	sf::Vector2f	dashStartPos;
	float			dashTime;
	float			currentTime;

	bool			isExtraDash;

private:
	void StartDash();

public:
	void Start() override;

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
public:
	SkeletonSpearSkill1State(SkeletonSpearFSM* fsm);
	~SkeletonSpearSkill1State();

};

