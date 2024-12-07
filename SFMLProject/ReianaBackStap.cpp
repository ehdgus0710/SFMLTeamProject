#include "stdafx.h"
#include "ReianaBackStap.h"
#include "Player.h"	
#include "Rigidbody.h"
#include "Animator.h"
#include "Animation.h"
#include "IntroLandSmoke.h"

ReianaBackStap::ReianaBackStap(ReianaFsm* fsm)
	: ReianaBaseState(fsm, ReianaStateType::BackStap)

{
}

ReianaBackStap::~ReianaBackStap()
{
}

void ReianaBackStap::BackStap(float deltaTime)
{
}

void ReianaBackStap::Awake()
{
	ReianaBaseState::Awake();
}

void ReianaBackStap::Start()
{
	ReianaBaseState::Start();
}

void ReianaBackStap::Enter()
{
	ReianaBaseState::Enter();
	animator->ChangeAnimation("dash", false);
	startPosition = { 2200.f,500.f };
	endPosition = { 1700.f,900.f };
	currentTime = 0.f;
	if (!reiana->IsFlipX())
		reiana->OnFlipX();
}

void ReianaBackStap::Exit()
{
	ReianaBaseState::Exit();
}

void ReianaBackStap::Update(float deltaTime)
{
	ReianaBaseState::Update(deltaTime);
	currentTime += deltaTime;
	reiana->SetPosition(sf::Vector2f::Lerp(startPosition, endPosition, currentTime / time*3));
	if (currentTime > time + 0.1)
	{
		SoundManger::GetInstance().PlaySfx("Leiana_MeteorGround_Ready", false);
		fsm->ChangeState(ReianaStateType::Idle);
		IntroLandSmoke* introLandSmoke = SCENE_MANAGER.GetCurrentScene()->AddGameObject(new IntroLandSmoke(), LayerType::EnemyBullet);
		introLandSmoke->SetScale({ 2.f,2.f });
		introLandSmoke->Start();
		introLandSmoke->SetPosition(reiana->GetPosition());
	}

}

void ReianaBackStap::FixedUpdate(float fixedDeltaTime)
{
	ReianaBaseState::FixedUpdate(fixedDeltaTime);
}

void ReianaBackStap::LateUpdate(float deltaTime)
{
	ReianaBaseState::LateUpdate(deltaTime);
}
