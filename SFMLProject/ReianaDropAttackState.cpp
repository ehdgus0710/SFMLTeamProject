#include "stdafx.h"
#include "ReianaDropAttackState.h"
#include "Player.h"
#include "Rigidbody.h"
#include "Animator.h"
#include "Animation.h"

ReianaDropAttackState::ReianaDropAttackState(ReianaFsm* fsm)
	:ReianaBaseState(fsm, ReianaStateType::DropAttack)
{
}

ReianaDropAttackState::~ReianaDropAttackState()
{
}

void ReianaDropAttackState::Wait(float deltaTime)
{
	currentWaitTime += deltaTime;

	if (currentWaitTime >= waitTime)
		action = true;
}

void ReianaDropAttackState::Drop(float deltaTime)
{
	currentDropTime += deltaTime;

	reiana->SetPosition(sf::Vector2f::Lerp(startPosition, endPosition, currentDropTime / dropTime));

	if (currentDropTime > dropTime)
		fsm->ChangeState(ReianaStateType::Idle);
	
}

void ReianaDropAttackState::Awake()
{
	ReianaBaseState::Awake();
}

void ReianaDropAttackState::Start()
{
	ReianaBaseState::Start();
}

void ReianaDropAttackState::Enter()
{
	ReianaBaseState::Enter();
	rigidbody = reiana->GetRigidbody();
	animator->ChangeAnimation("goldMeteorAttack", true);

	currentDropTime = 0.f;
	currentWaitTime = 0.f;
	action = false;
	auto playerPos = reiana->GetPlayer()->GetPosition();
	endPosition = { playerPos.x, 0.f };

	playerPos -= moveDistance;
	startPosition = playerPos;

	playerPos = reiana->GetPlayer()->GetPosition();
	
	

	reiana->SetPosition(startPosition);
	rigidbody->SetActive(false);
}

void ReianaDropAttackState::Exit()
{
	ReianaBaseState::Exit();
	rigidbody->SetActive(true);
}

void ReianaDropAttackState::Update(float deltaTime)
{
	ReianaBaseState::Update(deltaTime);

	if (!action)
		Wait(deltaTime);
	else
		Drop(deltaTime);
}

void ReianaDropAttackState::FixedUpdate(float fixedDeltaTime)
{
	ReianaBaseState::FixedUpdate(fixedDeltaTime);

}

void ReianaDropAttackState::LateUpdate(float deltaTime)
{
	ReianaBaseState::LateUpdate(deltaTime);

}