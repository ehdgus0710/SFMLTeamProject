#include "stdafx.h"
#include "B_ReianaDashState.h"
#include "Player.h"	
#include "Rigidbody.h"
#include "Animator.h"
#include "Animation.h"
#include "Camera.h"
#include "IntroLandSmoke.h"

B_ReianaDashState::B_ReianaDashState(B_ReianaFsm* fsm)
	: B_ReianaBaseState(fsm, B_ReianaStateType::Dash)

{
}

B_ReianaDashState::~B_ReianaDashState()
{
}

void B_ReianaDashState::BackStap(float deltaTime)
{
}

void B_ReianaDashState::Awake()
{
	B_ReianaBaseState::Awake();
}

void B_ReianaDashState::Start()
{
	B_ReianaBaseState::Start();
}

void B_ReianaDashState::Enter()
{
	B_ReianaBaseState::Enter();
	animator->ChangeAnimation("dash", false);
	movePosition = B_Reiana->GetPosition();
	cameraFixPos = SceneManager::GetInstance().GetCurrentScene()->GetMainCamera()->GetCameraPosition();
	cameraFixPos.x -= 1000.f;
	IntroLandSmoke* introLandSmoke = SCENE_MANAGER.GetCurrentScene()->AddGameObject(new IntroLandSmoke(), LayerType::EnemyBullet);
	introLandSmoke->Start();
	introLandSmoke->SetPosition(B_Reiana->GetPosition());
	if (B_Reiana->IsFlipX())
		B_Reiana->OnFlipX();
}

void B_ReianaDashState::Exit()
{
	B_ReianaBaseState::Exit();
}

void B_ReianaDashState::Update(float deltaTime)
{
	B_ReianaBaseState::Update(deltaTime);
	movePosition.x = movePosition.x - xSpeed * deltaTime;
	movePosition.y = movePosition.y - ySpeed * deltaTime;
	B_Reiana->SetPosition(movePosition);
	if (cameraFixPos.x >= B_Reiana->GetPosition().x)
	{
		B_Reiana->SetPosition({ B_Reiana->GetPosition().x -500,B_Reiana->GetPosition().y });
		fsm->ChangeState(B_ReianaStateType::Idle);
	}
}

void B_ReianaDashState::FixedUpdate(float fixedDeltaTime)
{
	B_ReianaBaseState::FixedUpdate(fixedDeltaTime);
}

void B_ReianaDashState::LateUpdate(float deltaTime)
{
	B_ReianaBaseState::LateUpdate(deltaTime);
}
