#pragma once
#include "SkeletonSpearBaseState.h"

class SkeletonSpearSkill2State : public SkeletonSpearBaseState
{
protected:
	Rigidbody* rigidbody;

	sf::Vector2f	dashEndPos;
	sf::Vector2f	dashStartPos;
	float			dashTime;
	float			currentTime;

	float			skillOnTime;
	float			skillEndTime;

	bool			isExtraDash;

private:
	void StartDash();

public:
	void Start() override;

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
public:
	SkeletonSpearSkill2State(SkeletonSpearFSM* fsm);
	~SkeletonSpearSkill2State();

};

