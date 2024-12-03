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

	if (!B_Reiana->IsFlipX() && B_Reiana->GetPosition().x > B_Reiana->GetPlayer()->GetPosition().x)
	{
		B_Reiana->OnFlipX();
	}
	if (B_Reiana->IsFlipX() && B_Reiana->GetPosition().x < B_Reiana->GetPlayer()->GetPosition().x)
	{
		B_Reiana->OnFlipX();
	}
	currentdelay = 0.f;
	count = reiana->GetCount();
	animator->ChangeAnimation("idle", true);

}

void B_ReianaIdleState::Exit()
{
	B_ReianaBaseState::Exit();

}

void B_ReianaIdleState::Update(float deltaTime)
{
	B_ReianaBaseState::Update(deltaTime);
	if (count < 6&&reiana->GetCount() != count)
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
			}
			else
			{
				count++;
				fsm->ChangeState(B_ReianaStateType::DropAttack);
				dash = false;
			}
			break;
		case B_ReianaStateType::Dead:
			fsm->ChangeState(B_ReianaStateType::Idle);
			break;
		case B_ReianaStateType::End:
			break;
		default:
			break;
		}
	}
}
