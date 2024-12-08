#include "stdafx.h"
#include "PlayerDashState.h"
#include "Rigidbody.h"
#include "Animator.h"
#include "Scene.h"
#include "Camera.h"
#include "Animation.h"
#include "AnimationGameObject.h"


PlayerDashState::PlayerDashState(PlayerFSM* fsm)
	: PlayerBaseState(fsm, PlayerStateType::Dash)
	, isExtraDash(false)
	, dashTime(0.25f)
	, currentTime(0.f)
	, rigidbody(nullptr)
	, isGround(false)
	, moveDirection(0.f)
{
	animationKeys.push_back("littleboneDash");
	animationKeys.push_back("noheadlittleboneDash");
	TEXTURE_MANAGER.Load("MeteorGroundSmoke", "graphics/boss/Rayanna/effects/MeteorGroundSmoke.png");
	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("DefaultDash", "AudioClip/Skul/Default_Dash.wav");
}

PlayerDashState::~PlayerDashState()
{
}

void PlayerDashState::StartDash()
{
	if (InputManager::GetInstance().GetKeyPressed(sf::Keyboard::Left))
	{
		if (!player->IsFlipX())
			player->OnFlipX();
	}
	else if (InputManager::GetInstance().GetKeyPressed(sf::Keyboard::Right))
	{
		if (player->IsFlipX())
			player->OnFlipX();
	}

	animator->ChangeAnimation(animationKeys[GetAnimationIndex()], false);
	moveDirection = player->IsFlipX() ? -1.f : 1.f;
	player->OnDash();
	currentTime = 0.f;
	CreateEffect();
}

void PlayerDashState::CreateEffect()
{
	AnimationGameObject* smoke = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new AnimationGameObject("DashSmoke"), LayerType::Effect);

	smoke->SetPosition(player->GetPosition() + (player->IsFlipX() ? sf::Vector2f::right * 32 : sf::Vector2f::left * 32));
	smoke->GetAnimator()->AddAnimation(new Animation("animations/Effect/dashSmoke.csv"), "dashSmoke");
	smoke->GetAnimator()->GetCurrentAnimation()->SetAnimationEndEvent(std::bind(&GameObject::OnDestory, smoke), smoke->GetAnimator()->GetCurrentAnimation()->GetEndFrameCount());
	smoke->GetAnimator()->Play();

	if (player->IsFlipX())
		smoke->OnFlipX();
	smoke->Start();

	SoundManger::GetInstance().PlaySfx("DefaultDash");
}

void PlayerDashState::Start()
{
	rigidbody = player->GetRigidbody();
}

void PlayerDashState::Enter()
{
	PlayerBaseState::Enter();
	rigidbody->ResetDropSpeed();
	rigidbody->ResetVelocity();

	isGround = rigidbody->IsGround();
	rigidbody->SetGround(true);
	isExtraDash = false;
	StartDash();
}

void PlayerDashState::Exit()
{
	rigidbody->SetGround(isGround);
	PlayerBaseState::Exit();
}

void PlayerDashState::Update(float deltaTime)
{
 	PlayerBaseState::Update(deltaTime);

	if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::Z))
		isExtraDash = true;

	currentTime += deltaTime;
	if (currentTime >= dashTime + 0.1f)
	{
		if (isExtraDash && player->GetCurrentDashCount() > 0)
		{
			StartDash();
		}
		else
		{
			if(rigidbody->IsGround())
				fsm->ChangeState(PlayerStateType::Idle);
			else
				fsm->ChangeState(PlayerStateType::Falling);
		}
	}

	if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::C) && player->GetCurrentJumpCount() > 0)
	{
		player->SetCurrentJumpCount(player->GetCurrentJumpCount() - 1);
		fsm->ChangeState(PlayerStateType::Jump);
	}
}

void PlayerDashState::FixedUpdate(float fixedDeltaTime)
{
	if (currentTime < dashTime)
		rigidbody->SetVelocity({ moveDirection * 1500.f , 0.f });
	else
		rigidbody->SetVelocity({0.f , 0.f });

}
