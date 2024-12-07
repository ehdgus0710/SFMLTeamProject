#pragma once
#include "SkeletonSpearBaseState.h"
class HitBoxObject;


class SkeletonSpearDashState : public SkeletonSpearBaseState
{
protected:
	Rigidbody* rigidbody;
	HitBoxObject* attackBox;
	DamegeInfo		damageInfo;

	sf::Vector2f	dashEndPos;
	sf::Vector2f	dashStartPos;
	float			dashTime;
	float			currentTime;

	bool			isExtraDash;

private:
	void StartDash();
	void OnCreateHitBox();
	void OnDestoryHitBox();
	void CreateEffect(GameObject* object);


public:
	void Start() override;

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
public:
	SkeletonSpearDashState(SkeletonSpearFSM* fsm);
	~SkeletonSpearDashState();

};


