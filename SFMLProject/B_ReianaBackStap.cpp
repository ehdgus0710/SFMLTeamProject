#include "stdafx.h"
#include "B_ReianaBackStap.h"
#include "Player.h"	
#include "Rigidbody.h"
#include "Animator.h"
#include "Animation.h"
#include "IntroLandSmoke.h"

B_ReianaBackStap::B_ReianaBackStap(B_ReianaFsm* fsm)
	: B_ReianaBaseState(fsm, B_ReianaStateType::BackStap)

{
}

B_ReianaBackStap::~B_ReianaBackStap()
{
}

void B_ReianaBackStap::BackStap(float deltaTime)
{
}

void B_ReianaBackStap::Awake()
{
	B_ReianaBaseState::Awake();
}

void B_ReianaBackStap::Start()
{
	B_ReianaBaseState::Start();
}

void B_ReianaBackStap::Enter()
{
	B_ReianaBaseState::Enter();
	animator->ChangeAnimation("dash", false);
	startPosition = { -300.f,500.f };
	endPosition = { 200.f,900.f };
	currentTime = 0.f;
	if(b_reiana->IsFlipX())
		b_reiana->OnFlipX();
}

void B_ReianaBackStap::Exit()
{
	B_ReianaBaseState::Exit();
}

void B_ReianaBackStap::Update(float deltaTime)
{
	B_ReianaBaseState::Update(deltaTime);
	currentTime += deltaTime;
	b_reiana->SetPosition(sf::Vector2f::Lerp(startPosition, endPosition, currentTime / time*3));
	if (currentTime > time + 0.1)
	{
		fsm->ChangeState(B_ReianaStateType::Idle);
		IntroLandSmoke* introLandSmoke = SCENE_MANAGER.GetCurrentScene()->AddGameObject(new IntroLandSmoke(), LayerType::EnemyBullet);
		introLandSmoke->SetScale({ 2.f,2.f });
		introLandSmoke->Start();
		introLandSmoke->SetPosition(b_reiana->GetPosition());
	}

}

void B_ReianaBackStap::FixedUpdate(float fixedDeltaTime)
{
	B_ReianaBaseState::FixedUpdate(fixedDeltaTime);
}

void B_ReianaBackStap::LateUpdate(float deltaTime)
{
	B_ReianaBaseState::LateUpdate(deltaTime);
}
