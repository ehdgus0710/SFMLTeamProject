#include "stdafx.h"
#include "ReianaGroundAttackState.h"
#include "Player.h"	
#include "Rigidbody.h"
#include "Animator.h"
#include "Animation.h"

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
	endPosition = reiana->GetPosition();
	startPosition = { 1700.f ,reiana->GetPosition().y };
	reiana->SetPosition(startPosition);
	endPosition = reiana->GetPosition() + sf::Vector2f::left * moveDistance;
	animator->ChangeAnimation("meteorAttack", false);
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

void ReianaGroundAttackState::ChangeReady2Animation()
{
	int endFrame = (int)animator->GetCurrentAnimation()->GetFrameInfo().size() - 1;
	animator->GetCurrentAnimation()->ClearEndEvent(endFrame);

	animator->ChangeAnimation("meteorGround2Ready", false);
}

void ReianaGroundAttackState::Awake()
{
	ReianaBaseState::Awake();
}

void ReianaGroundAttackState::Start()
{
	ReianaBaseState::Start();
}

void ReianaGroundAttackState::Enter()
{
	ReianaBaseState::Enter();
	animator->ChangeAnimation("meteorGroundReady", false);

	int endFrame = (int)animator->GetCurrentAnimation()->GetFrameInfo().size() - 1;
	animator->GetCurrentAnimation()->SetAnimationEndEvent(std::bind(&ReianaGroundAttackState::ChangeReady2Animation, this), endFrame);

	if(!reiana->IsFlipX())
		reiana->OnFlipX();

	currentAttackTime = 0.f;
	currentWaitTime = 0.f;
	action = false;
	auto playerPos = reiana->GetPlayer()->GetPosition();

	startPosition = { 1700.f ,reiana->GetPosition().y };
	reiana->SetPosition(startPosition);
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