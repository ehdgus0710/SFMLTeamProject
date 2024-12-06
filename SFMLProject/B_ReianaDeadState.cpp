#include "stdafx.h"
#include "B_ReianaDeadState.h"
#include "Animator.h"
#include "Animation.h"
#include "Awakning.h"
#include "AwakeReiana.h"

B_ReianaDeadState::B_ReianaDeadState(B_ReianaFsm* fsm)
	:B_ReianaBaseState(fsm, B_ReianaStateType::Dead)
{
}

B_ReianaDeadState::~B_ReianaDeadState()
{
}

void B_ReianaDeadState::Enter()
{
	Awakning* awakning = SCENE_MANAGER.GetCurrentScene()->AddGameObject(new Awakning(""), LayerType::EnemyBullet);
	awakning->SetPosition(b_reiana->GetPosition());
	awakning->Start();
	int EndFream = animator->GetCurrentAnimation()->GetFrameInfo().size() - 1;
	animator->ChangeAnimation("awaken", false);
	animator->GetCurrentAnimation()->SetAnimationEndEvent(std::bind(&B_ReianaDeadState::SetAwakenReiana, this), 30);
}

void B_ReianaDeadState::SetAwakenReiana()
{
	b_reiana->SetActive(false);
	AwakeReiana* awakeReiana = SCENE_MANAGER.GetCurrentScene()->AddGameObject(new AwakeReiana(""), LayerType::Enemy);
	awakeReiana->SetPosition(b_reiana->GetPosition());
	awakeReiana->Start();
}

