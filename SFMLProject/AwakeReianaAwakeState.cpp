#include "stdafx.h"
#include "AwakeReianaAwakeState.h"
#include "Animator.h"
#include "Animation.h"
#include "Rigidbody.h"
#include "Collider.h"

AwakeReianaAwakeState::AwakeReianaAwakeState(AwakeReianaFsm* fsm)
	:AwakeReianaBaseState(fsm, AwakeReianaStateType::Dead)
{
}

AwakeReianaAwakeState::~AwakeReianaAwakeState()
{
}

void AwakeReianaAwakeState::Enter()
{
	AwakeReianaBaseState::Enter();
	animator->ChangeAnimation("dead", false);
	SoundManger::GetInstance().PlayBgm("Chapter2_Boss_Awaken", true);
	SoundManger::GetInstance().PlaySfx("Leiana_Awakening_Impact", false);
	awakeTiem = 1.f;
	awakeCurrentTime = 0.f;

	awakeReiana->GetRigidbody()->SetActive(false);
	awakeReiana->GetCollider()->SetActive(false);
}
void AwakeReianaAwakeState::Update(float deltaTime)
{
	AwakeReianaBaseState::Update(deltaTime);
	awakeCurrentTime += deltaTime;
	if (awakeTiem < awakeCurrentTime)
	{
		fsm->ChangeState(AwakeReianaStateType::Idle);
		awakeReiana->GetRigidbody()->SetActive(true);
		awakeReiana->GetCollider()->SetActive(true);
	}
}

