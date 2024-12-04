#include "stdafx.h"
#include "AwakeReianaIdleState.h"
#include "Animator.h"
#include "Player.h"

AwakeReianaIdleState::AwakeReianaIdleState(AwakeReianaFsm* fsm)
	: AwakeReianaBaseState(fsm, AwakeReianaStateType::Idle)
{
}

AwakeReianaIdleState::~AwakeReianaIdleState()
{
}
void AwakeReianaIdleState::Awake()
{
	AwakeReianaBaseState::Awake();
}

void AwakeReianaIdleState::Start()
{
	AwakeReianaBaseState::Start();
}

void AwakeReianaIdleState::Enter()
{
	AwakeReianaBaseState::Enter();


	currentdelay = 0.f;
	if (AwakeReiana->GetPosition().x < AwakeReiana->GetPlayer()->GetPosition().x && AwakeReiana->IsFlipX())
	{
		AwakeReiana->OnFlipX();
	}
	if (AwakeReiana->GetPosition().x > AwakeReiana->GetPlayer()->GetPosition().x && !AwakeReiana->IsFlipX())
	{
		AwakeReiana->OnFlipX();
	}
	animator->ChangeAnimation("awakenIdle", true);
	AwakeReiana->SetCount(count);
	if (count == 9)
	{
		count = 1;
	}
}

void AwakeReianaIdleState::Exit()
{
	AwakeReianaBaseState::Exit();

}

void AwakeReianaIdleState::Update(float deltaTime)
{
	AwakeReianaBaseState::Update(deltaTime);
	changeState(deltaTime);
}

void AwakeReianaIdleState::FixedUpdate(float fixedDeltaTime)
{
	AwakeReianaBaseState::FixedUpdate(fixedDeltaTime);

}

void AwakeReianaIdleState::LateUpdate(float deltaTime)
{
	AwakeReianaBaseState::LateUpdate(deltaTime);

}


void AwakeReianaIdleState::changeState(float dt)
{
	currentdelay += dt;
	if (currentdelay > delay)
	{
		switch ((AwakeReianaStateType)count)
		{
		case AwakeReianaStateType::AwakeDimension:
			count++;
			tossCount++;
			fsm->ChangeState(AwakeReianaStateType::AwakeDimension);
			break;
		case AwakeReianaStateType::Dimension:
			count++;
			fsm->ChangeState(AwakeReianaStateType::Dimension);
			break;
		case AwakeReianaStateType::DropAttack:
			count++;
			fsm->ChangeState(AwakeReianaStateType::DropAttack);
			break;
		case AwakeReianaStateType::GroundAttack:
			count++;
			tossCount++;
			fsm->ChangeState(AwakeReianaStateType::GroundAttack);
			break;
		case AwakeReianaStateType::Dead:
			count++;
			fsm->ChangeState(AwakeReianaStateType::Dead);
			break;
		case AwakeReianaStateType::End:
			break;
		default:
			break;
		}
	}
}
