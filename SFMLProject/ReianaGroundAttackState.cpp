#include "stdafx.h"
#include "ReianaGroundAttackState.h"
#include "Player.h"	
#include "Rigidbody.h"

ReianaGroundAttackState::ReianaGroundAttackState(ReianaFsm* fsm)
	: ReianaBaseState(fsm, ReianaStateType::GroundAttack)

{
}

ReianaGroundAttackState::~ReianaGroundAttackState()
{
}

void ReianaGroundAttackState::Attack(float deltaTime)
{
	currentAttackTime += deltaTime;

	reiana->SetPosition(sf::Vector2f::Lerp(startPosition, endPosition, currentAttackTime / attackTime));

	if (currentAttackTime > attackTime)
		fsm->ChangeState(ReianaStateType::Idle);
}

void ReianaGroundAttackState::Wait(float deltaTime)
{
	currentWaitTime += deltaTime;

	if (currentWaitTime >= waitTime)
		action = true;
}

void ReianaGroundAttackState::Awake()
{
}

void ReianaGroundAttackState::Start()
{
}

void ReianaGroundAttackState::Enter()
{
	ReianaBaseState::Enter();

	currentAttackTime = 0.f;
	currentWaitTime = 0.f;
	action = false;
	auto playerPos = reiana->GetPlayer()->GetPosition();

	endPosition = reiana->GetPosition();
	startPosition = { 1700.f ,reiana->GetPosition().y };
	reiana->SetPosition(startPosition);
	endPosition = reiana->GetPosition() + sf::Vector2f::left * moveDistance;
}

void ReianaGroundAttackState::Exit()
{
	ReianaBaseState::Exit();
}

void ReianaGroundAttackState::Update(float deltaTime)
{
	ReianaBaseState::Update(deltaTime);
	
	if (!action)
		Wait(deltaTime);
	else
		Attack(deltaTime);
}

void ReianaGroundAttackState::FixedUpdate(float fixedDeltaTime)
{
	ReianaBaseState::FixedUpdate(fixedDeltaTime);
}

void ReianaGroundAttackState::LateUpdate(float deltaTime)
{
	ReianaBaseState::LateUpdate(deltaTime);
}
