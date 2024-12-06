#include "stdafx.h"
#include "B_ReianaIdleState.h"
#include "Animator.h"
#include "Player.h"
#include "Reiana.h"

B_ReianaIdleState::B_ReianaIdleState(B_ReianaFsm* fsm)
	: B_ReianaBaseState(fsm, B_ReianaStateType::Idle)
{
}

B_ReianaIdleState::~B_ReianaIdleState()
{
}
void B_ReianaIdleState::Awake()
{
	B_ReianaBaseState::Awake();
}

void B_ReianaIdleState::Start()
{
	B_ReianaBaseState::Start();
}

void B_ReianaIdleState::Enter()
{
	B_ReianaBaseState::Enter();

	reiana = dynamic_cast<Reiana*>(SCENE_MANAGER.GetCurrentScene()->FindGameObject("Reiana", LayerType::Boss));

	if (!b_reiana->IsFlipX() && b_reiana->GetPosition().x > b_reiana->GetPlayer()->GetPosition().x)
	{
		b_reiana->OnFlipX();
	}
	if (b_reiana->IsFlipX() && b_reiana->GetPosition().x < b_reiana->GetPlayer()->GetPosition().x)
	{
		b_reiana->OnFlipX();
	}
	currentdelay = 0.f;

	count = reiana->GetCount();
	animator->ChangeAnimation("idle", true);

	if (reiana->GetHp() <= 0)
	{
		fsm->ChangeState(B_ReianaStateType::Dead);
	}
}

void B_ReianaIdleState::Exit()
{
	B_ReianaBaseState::Exit();

}

void B_ReianaIdleState::Update(float deltaTime)
{
	B_ReianaBaseState::Update(deltaTime);
	if (count <= 9 && reiana->GetCount() != count)
	{
		currentdelay = 0.f;
		count = reiana->GetCount();
	}
	changeState(deltaTime);
}

void B_ReianaIdleState::FixedUpdate(float fixedDeltaTime)
{
	B_ReianaBaseState::FixedUpdate(fixedDeltaTime);

}

void B_ReianaIdleState::LateUpdate(float deltaTime)
{
	B_ReianaBaseState::LateUpdate(deltaTime);

}


void B_ReianaIdleState::changeState(float dt)
{
	currentdelay += dt;
	if (currentdelay > delay)
	{
		switch ((B_ReianaStateType)count)
		{
		case B_ReianaStateType::Dash:
			fsm->ChangeState(B_ReianaStateType::Dash);
			break;
		case B_ReianaStateType::BackStap:
			fsm->ChangeState(B_ReianaStateType::BackStap);
			break;
		case B_ReianaStateType::GroundAttack:
			fsm->ChangeState(B_ReianaStateType::GroundAttack);
			break;
		case B_ReianaStateType::ThreeSword:
			fsm->ChangeState(B_ReianaStateType::ThreeSword);
			break;
		case B_ReianaStateType::None2:
			count++;
			currentdelay = 0.f;
			break;
		case B_ReianaStateType::DropAttack:
			if (!dash)
			{
				fsm->ChangeState(B_ReianaStateType::Dash);
				dash = true;
				delay = 2.0;
			}
			else
			{
				fsm->ChangeState(B_ReianaStateType::DropAttack);
				dash = false;
				count++;
				delay = 1.0;
			}
			break;
		case B_ReianaStateType::Dead:
			fsm->ChangeState(B_ReianaStateType::Dead);
			break;
		case B_ReianaStateType::End:
			break;
		default:
			break;
		}
	}
}
