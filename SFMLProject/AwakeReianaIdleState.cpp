#include "stdafx.h"
#include "AwakeReianaIdleState.h"
#include "Animator.h"
#include "Player.h"
#include "Collider.h"

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
	animator->ChangeAnimation("awakenIdle", true);
	awakeReiana->SetCount(count);
	if (awakeReiana->GetPosition().x < awakeReiana->GetPlayer()->GetPosition().x && !awakeReiana->IsFlipX())
	{
		awakeReiana->OnFlipX();
	}
	if (awakeReiana->GetPosition().x > awakeReiana->GetPlayer()->GetPosition().x && awakeReiana->IsFlipX())
	{
		awakeReiana->OnFlipX();
	}
	if (count == 5)
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
	currentStartDelay += deltaTime;

	if (!start && startDelay <= currentStartDelay)
	{
		start = true;
	}
	if (start)
	{
		changeState(deltaTime);
	}
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
