#include "stdafx.h"
#include "ReianaIdleState.h"
#include "Animator.h"
#include "Player.h"

ReianaIdleState::ReianaIdleState(ReianaFsm* fsm)
	: ReianaBaseState(fsm, ReianaStateType::Idle)
{
}

ReianaIdleState::~ReianaIdleState()
{
}
void ReianaIdleState::Awake()
{
	ReianaBaseState::Awake();
}

void ReianaIdleState::Start()
{
	ReianaBaseState::Start();
}

void ReianaIdleState::Enter()
{
	ReianaBaseState::Enter();


	currentdelay = 0.f;
	if (reiana->GetPosition().x < reiana->GetPlayer()->GetPosition().x && reiana->IsFlipX())
	{
		reiana->OnFlipX();
	}
	if (reiana->GetPosition().x > reiana->GetPlayer()->GetPosition().x && !reiana->IsFlipX())
	{
		reiana->OnFlipX();
	}
	animator->ChangeAnimation("idle", true);
	reiana->SetCount(count);
	if (count == 9)
	{
		count = 1;
	}
}

void ReianaIdleState::Exit()
{
	ReianaBaseState::Exit();

}

void ReianaIdleState::Update(float deltaTime)
{
	ReianaBaseState::Update(deltaTime);
	changeState(deltaTime);
}

void ReianaIdleState::FixedUpdate(float fixedDeltaTime)
{
	ReianaBaseState::FixedUpdate(fixedDeltaTime);

}

void ReianaIdleState::LateUpdate(float deltaTime)
{
	ReianaBaseState::LateUpdate(deltaTime);

}


void ReianaIdleState::changeState(float dt)
{
	currentdelay += dt;
	if (currentdelay > delay)
	{
		switch ((ReianaStateType)count)
		{
		case ReianaStateType::NomalAttack:
			count++;
			tossCount++;
			fsm->ChangeState(ReianaStateType::NomalAttack);
			break;
		case ReianaStateType::Dash:
			count++;
			fsm->ChangeState(ReianaStateType::Dash);
			break;
		case ReianaStateType::BackStap:
			count++;
			fsm->ChangeState(ReianaStateType::BackStap);
			break;
		case ReianaStateType::GroundAttack:
			count++;
			tossCount++;
			fsm->ChangeState(ReianaStateType::GroundAttack);
			break;
		case ReianaStateType::ThreeSword:
			count++;
			tossCount++;
			fsm->ChangeState(ReianaStateType::ThreeSword);
			break;
		case ReianaStateType::Dimension:
			count++;
			fsm->ChangeState(ReianaStateType::Dimension);
			break;
		case ReianaStateType::DropAttack:
			if (!dash)
			{
				fsm->ChangeState(ReianaStateType::Dash);
				dash = true;
			}
			else
			{
				count++;
				tossCount++;
				fsm->ChangeState(ReianaStateType::DropAttack);
				dash = false;
			}
			break;
		case ReianaStateType::Rising:
			count++;
			fsm->ChangeState(ReianaStateType::Rising);
			break;
		case ReianaStateType::Dead:
			count++;
			fsm->ChangeState(ReianaStateType::Idle);
			break;
		case ReianaStateType::End:
			break;
		default:
			break;
		}
	}
}
