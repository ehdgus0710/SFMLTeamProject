#include "stdafx.h"
#include "ReianaDashState.h"
#include "Player.h"	
#include "Rigidbody.h"
#include "Animator.h"
#include "Animation.h"
#include "Camera.h"

ReianaDashState::ReianaDashState(ReianaFsm* fsm)
	: ReianaBaseState(fsm, ReianaStateType::Dash)

{
}

ReianaDashState::~ReianaDashState()
{
}

void ReianaDashState::BackStap(float deltaTime)
{
}

void ReianaDashState::Awake()
{
	ReianaBaseState::Awake();
}

void ReianaDashState::Start()
{
	ReianaBaseState::Start();
}

void ReianaDashState::Enter()
{
	ReianaBaseState::Enter();
	animator->ChangeAnimation("dash", false);
	if (reiana->IsFlipX())
		reiana->OnFlipX();
	movePosition = reiana->GetPosition();
	cameraFixPos = SceneManager::GetInstance().GetCurrentScene()->GetMainCamera()->GetCameraPosition();
	cameraFixPos.x += 1000.f;
}

void ReianaDashState::Exit()
{
	ReianaBaseState::Exit();
}

void ReianaDashState::Update(float deltaTime)
{
	ReianaBaseState::Update(deltaTime);
	movePosition.x = movePosition.x + xSpeed * deltaTime;
	movePosition.y = movePosition.y - ySpeed * deltaTime;
	reiana->SetPosition(movePosition);
	if (cameraFixPos.x <= reiana->GetPosition().x)
	{
		reiana->SetPosition({ reiana->GetPosition().x,-30.f });
	}
}

void ReianaDashState::FixedUpdate(float fixedDeltaTime)
{
	ReianaBaseState::FixedUpdate(fixedDeltaTime);
}

void ReianaDashState::LateUpdate(float deltaTime)
{
	ReianaBaseState::LateUpdate(deltaTime);
}
