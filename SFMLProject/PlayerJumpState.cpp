#include "stdafx.h"
#include "PlayerJumpState.h"
#include "Rigidbody.h"
#include "Animator.h"
#include "Animation.h"

PlayerJumpState::PlayerJumpState(PlayerFSM* fsm)
	: PlayerBaseState(fsm, PlayerStateType::Jump)
{
	animationKeys.push_back("littleboneJump");
	animationKeys.push_back("noheadlittleboneJump");
	TEXTURE_MANAGER.Load("goldMeteorLandingSmoke", "graphics/boss/Rayanna/effects/goldMeteorLandingSmoke.png");
	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("DefaultJump", "AudioClip/Skul/Default_Jump.wav");
}

PlayerJumpState::~PlayerJumpState()
{
}

void PlayerJumpState::CreateExtraEffet()
{
	AnimationGameObject* smoke = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new AnimationGameObject("extraJumpSmoke"), LayerType::Effect);

	smoke->SetPosition(player->GetPosition() + sf::Vector2f::down * 16.f);
	smoke->GetAnimator()->AddAnimation(new Animation("animations/Effect/extraJumpSmoke.csv"), "extraJumpSmoke");
	smoke->GetAnimator()->GetCurrentAnimation()->SetAnimationEndEvent(std::bind(&GameObject::OnDestory, smoke), smoke->GetAnimator()->GetCurrentAnimation()->GetEndFrameCount());
	smoke->SetScale(sf::Vector2f::one * 2.f);
	smoke->GetAnimator()->Play();
	smoke->Start();
}

void PlayerJumpState::Awake()
{
	PlayerBaseState::Awake();
}

void PlayerJumpState::Start()
{
	rigidbody = player->GetRigidbody();
}

void PlayerJumpState::Enter()
{
	PlayerBaseState::Enter();

	animator->ChangeAnimation(animationKeys[GetAnimationIndex()], false);

	player->SetIsJump(true);
	rigidbody->SetGround(false);
	rigidbody->ResetDropSpeed();
	rigidbody->SetVelocity({ rigidbody->GetCurrentVelocity().x, -800.f });

	SoundManger::GetInstance().PlaySfx("DefaultJump");
}

void PlayerJumpState::Exit()
{
	PlayerBaseState::Exit();
	horizontal = 0.f;
}

void PlayerJumpState::Update(float deltaTime)
{
	if (rigidbody->IsGround())
	{
		fsm->ChangeState(PlayerStateType::Idle);
		return;
	}
	horizontal = player->GetMoveDirection();

	if (KeyActionManager::GetInstance().GetKeyPressed(KeyActionType::LeftMove) &&
		KeyActionManager::GetInstance().GetKeyPressed(KeyActionType::RightMove))
	{
		horizontal = 0.f;
	}
	else if (KeyActionManager::GetInstance().GetKeyPressed(KeyActionType::LeftMove))
	{
		horizontal = -1.f;
	}
	else if (KeyActionManager::GetInstance().GetKeyPressed(KeyActionType::RightMove))
	{
		horizontal = 1.f;
	}
	else
		horizontal = 0.f;
	player->SetMoveDirection(horizontal);

	if (KeyActionManager::GetInstance().GetKeyPressed(KeyActionType::Dash) && player->GetCurrentDashCount() > 0)
	{
		fsm->ChangeState(PlayerStateType::Dash);
		return;
	}

	if (KeyActionManager::GetInstance().GetKeyDown(KeyActionType::Jump) && player->GetCurrentJumpCount() > 0)
	{
		player->SetCurrentJumpCount(player->GetCurrentJumpCount() - 1);
		fsm->ChangeState(PlayerStateType::Jump);
		CreateExtraEffet();
		return;
	}
	if (KeyActionManager::GetInstance().GetKeyUp(KeyActionType::Attack))
	{
		fsm->ChangeState(PlayerStateType::JumpAttack);
		return;
	}

	if ((horizontal < 0.f && !player->IsFlipX()) || (horizontal > 0.f && player->IsFlipX()))
		player->OnFlipX();
}

void PlayerJumpState::FixedUpdate(float fixedDeltaTime)
{
	rigidbody->SetVelocity({ horizontal * player->GetSpeed() , rigidbody->GetCurrentVelocity().y });
}