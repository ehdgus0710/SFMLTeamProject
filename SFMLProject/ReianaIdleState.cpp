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
	if (reiana->IsFlipX() && reiana->GetPosition().x > reiana->GetPlayer()->GetPosition().x)
	{
		reiana->OnFlipX();
	}
	if (!reiana->IsFlipX() && reiana->GetPosition().x < reiana->GetPlayer()->GetPosition().x)
	{
		reiana->OnFlipX();
	}
	animator->ChangeAnimation("idle", true);

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
			fsm->ChangeState(ReianaStateType::NomalAttack);
			break;
		case ReianaStateType::Dash:
			count++;
			fsm->ChangeState(ReianaStateType::Dash);
			break;
		case ReianaStateType::GroundAttack:
			count++;
			fsm->ChangeState(ReianaStateType::GroundAttack);
			break;
		case ReianaStateType::ThreeSword:
			count++;
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
