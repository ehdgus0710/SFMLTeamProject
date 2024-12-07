#include "stdafx.h"
#include "ReianaDashState.h"
#include "Player.h"	
#include "Rigidbody.h"
#include "Animator.h"
#include "Animation.h"
#include "Camera.h"
#include "IntroLandSmoke.h"

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
	movePosition = reiana->GetPosition();
	cameraFixPos = SceneManager::GetInstance().GetCurrentScene()->GetMainCamera()->GetCameraPosition();
	cameraFixPos.x += 1000.f;
	IntroLandSmoke* introLandSmoke = SCENE_MANAGER.GetCurrentScene()->AddGameObject(new IntroLandSmoke(), LayerType::EnemyBullet);
	introLandSmoke->Start();
	introLandSmoke->SetPosition(reiana->GetPosition());
	if (reiana->IsFlipX())
		reiana->OnFlipX();
}

void ReianaDashState::Exit()
{
	ReianaBaseState::Exit();
}

void ReianaDashState::Update(float deltaTime)
{
	ReianaBaseState::Update(deltaTime);
	movePosition.x = movePosition.x + xSpeed * deltaTime*3;
	movePosition.y = movePosition.y - ySpeed * deltaTime*3;
	reiana->SetPosition(movePosition);
	if (cameraFixPos.x <= reiana->GetPosition().x)
	{
		reiana->SetPosition({ reiana->GetPosition().x + 500,reiana->GetPosition().y});
		fsm->ChangeState(ReianaStateType::Idle);
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
