#include "stdafx.h"
#include "PlayerJumpAttackState.h"

#include "Rigidbody.h"
#include "Animation.h"
#include "Animator.h"
#include "HitBoxObject.h"

PlayerJumpAttackState::PlayerJumpAttackState(PlayerFSM* fsm)
	: PlayerBaseState(fsm, PlayerStateType::JumpAttack)
	, rigidbody(nullptr)
	, horizontal(0)
	, attackBox(nullptr)
	, sequenceAttack(false)
{
	animationKeys.push_back("littleboneJumpAttack");
	animationKeys.push_back("noheadlittleboneJumpAttack");

	damageInfo.damege = 10.f;
	damageInfo.useKnockback = true;
	damageInfo.knockbackDuration = 0.2f;
	damageInfo.owner = player;
	damageInfo.knockbackVelocity = { 30.f,0.f };
	damageInfo.hitDirection = sf::Vector2f::down;

	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("SkulJumpAtk", "AudioClip/Skul/Skul_Jump_Atk.wav");
}

PlayerJumpAttackState::~PlayerJumpAttackState()
{
}

void PlayerJumpAttackState::SetChangeAnimationKey(int index)
{
	ClearEvenet();
	PlayerBaseState::SetChangeAnimationKey(index);
	SetAttackEvnet();
}

void PlayerJumpAttackState::Start()
{
	rigidbody = player->GetRigidbody();
}

void PlayerJumpAttackState::Enter()
{
	PlayerBaseState::Enter();

	animator->ChangeAnimation(animationKeys[GetAnimationIndex()], false);
	OnStartAttack();
}

void PlayerJumpAttackState::Exit()
{
	ClearEvenet();

	if (attackBox)
	{
		OnDestoryHitBox();
	}

	PlayerBaseState::Exit();
	horizontal = 0.f;
	sequenceAttack = false;
}

void PlayerJumpAttackState::Update(float deltaTime)
{
	if (rigidbody->IsGround())
	{
		player->SetCurrentJumpCount(player->GetJumpCount());

		fsm->ChangeState(PlayerStateType::Idle);
		return;
	}

	if (InputManager::GetInstance().GetKeyPressed(sf::Keyboard::Left))
	{
		horizontal = -1.f;
	}
	if (InputManager::GetInstance().GetKeyPressed(sf::Keyboard::Right))
	{
		horizontal = 1.f;
	}
	if (InputManager::GetInstance().GetKeyPressed(sf::Keyboard::X))
		sequenceAttack = true;

	player->SetMoveDirection(horizontal);
}

void PlayerJumpAttackState::FixedUpdate(float fixedDeltaTime)
{
	rigidbody->SetVelocity({ horizontal * player->GetSpeed() * 0.5f , rigidbody->GetCurrentVelocity().y });
}

void PlayerJumpAttackState::OnStartAttack()
{
	Animation* animation = animator->GetCurrentAnimation();
	animation->Reset();
	animation->Play(1.f, false);
	SetAttackEvnet();
	sequenceAttack = false;
}

void PlayerJumpAttackState::OnEndAttack()
{
	if (!rigidbody->IsGround())
	{
		if (sequenceAttack)
		{
			animator->GetCurrentAnimation()->ClearEndEvent(animator->GetCurrentAnimation()->GetEndFrameCount());
			OnStartAttack();
		}
		else
			fsm->ChangeState(PlayerStateType::Falling);
	}
	else
	{
		fsm->ChangeState(PlayerStateType::Idle);
		player->SetCurrentJumpCount(player->GetJumpCount());
	}
}


void PlayerJumpAttackState::OnCreateHitBox()
{
	if (attackBox)
		attackBox->OnDestory();

	attackBox = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new HitBoxObject(player, ColliderLayer::PlayerBullet, ColliderLayer::Boss, true, (sf::Vector2f::right * 30.f)), LayerType::PlayerBullet);
	attackBox->SetScale({ 50.f,50.f });

	attackBox->SetDamage(damageInfo);
	attackBox->AddStartHitEvent(std::bind(&PlayerJumpAttackState::CreateEffect, this, std::placeholders::_1));
	attackBox->AddStartHitEvent(std::bind(&Player::OnAttackHitSound, player, std::placeholders::_1));

	SoundManger::GetInstance().PlaySfx("SkulJumpAtk");
}

void PlayerJumpAttackState::OnDestoryHitBox()
{
	attackBox->OnDestory();
	attackBox->SetActive(false);
	attackBox = nullptr;

	Animation* animation = animator->GetCurrentAnimation();
	animation->ClearStartEvent(1);
	animation->ClearEndEvent(1);
}

void PlayerJumpAttackState::ClearEvenet()
{
	Animation* animation = animator->GetAnimation(animationKeys[GetAnimationIndex()]);
	animation->ClearEndEvent(animation->GetFrameCount() - 1);
	animation->ClearStartEvent(1);
	animation->ClearEndEvent(1);
}

void PlayerJumpAttackState::SetAttackEvnet()
{
	Animation* animation = animator->GetCurrentAnimation();
	animation->SetAnimationEndEvent(std::bind(&PlayerJumpAttackState::OnEndAttack, this), animation->GetEndFrameCount());
	animation->SetAnimationStartEvent(std::bind(&PlayerJumpAttackState::OnCreateHitBox, this), 1);
	animation->SetAnimationEndEvent(std::bind(&PlayerJumpAttackState::OnDestoryHitBox, this), 1);
}

void PlayerJumpAttackState::CreateEffect(GameObject* object)
{
	AnimationGameObject* effect = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new AnimationGameObject("AttackEffect"), LayerType::Effect);
	Animation* animation(new Animation("animations/Effect/normalAttack.csv"));
	effect->GetAnimator()->AddAnimation(animation, "NormalAttack");
	effect->GetAnimator()->ChangeAnimation("NormalAttack");

	animation->SetAnimationEndEvent(std::bind(&GameObject::OnDestory, effect), animation->GetEndFrameCount());
	effect->SetPosition(object->GetPosition());

	if (player->IsFlipX())
		effect->SetScale({ effect->GetScale().x * -2.f ,effect->GetScale().y * 2.f });
	else
		effect->SetScale(sf::Vector2f::one * 2.f);

	effect->Awake();
	effect->Start();
}
