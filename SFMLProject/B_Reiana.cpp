#include "stdafx.h"
#include "B_Reiana.h"
#include "Rigidbody.h"

#include "Collider.h"
#include "Animation.h"
#include "Animator.h"
#include "Player.h"
#include "Reiana.h"

B_Reiana::B_Reiana(const std::string& name)
	:AnimationGameObject(name)
	, fsm(this)
{
	rigidBody = new Rigidbody(this);
	rigidBody->SetGround(false);
	CreateCollider(ColliderType::Rectangle, ColliderLayer::Reiana);


	animator->LoadCsv("animators/rayanna.csv");
	animator->ChangeAnimation("meteorAttack", false);

	currentStatus.hp = 150;
	currentStatus.maxHp = 150;

	// animator->CreateAnimation("B_ReianaIdle", "B_ReianaIdle", { 150, 192 }, 1, 0.1f, true);
}

B_Reiana::~B_Reiana()
{
}

void B_Reiana::TakeDamage(const DamegeInfo& damage)
{
	currentStatus.hp -= damage.damege;

	if (currentStatus.hp <= 0.f)
	{
		currentStatus.hp = 0.f;
		OnDead();
		/*isDead = true;
		fsm.ChangeState(PlayerStateType::Dead);*/

		/*if (!phaseUp)
		{
			phaseUp = true;
			currentStatus.hp = (float)phase2Hp;
			currentStatus.maxHp = (float)phase2Hp;
			yggdrasilUIHub->ChangePhase();
		}*/
	}

	if (changeHpAction != nullptr)
		changeHpAction(currentStatus.hp, currentStatus.maxHp);
}

void B_Reiana::OnDead()
{
	// fsm.ChangeState(B_ReianaStateType::Dead);
}

void B_Reiana::Awake()
{
	AnimationGameObject::Awake();
}

void B_Reiana::Start()
{
	InputManager::GetInstance().BindKey(sf::Keyboard::W);

	collider->SetOffsetPosition({ 0.f,-100.f });
	reiana = dynamic_cast<Reiana*>(SCENE_MANAGER.GetCurrentScene()->FindGameObject("Reiana", LayerType::Boss));
	player = dynamic_cast<Player*>(SCENE_MANAGER.GetCurrentScene()->FindGameObject("Player", LayerType::Player));
	AnimationGameObject::Start();
	animator->ChangeAnimation("B_ReianaIdle", true);
	fsm.ChangeState(B_ReianaStateType::Idle);
	collider->SetScale({ 60.f,60.f });
	SetOrigin(Origins::BottomCenter);
	SetScale({ -3.5f,3.5f });
	OnFlipX();


	if (changeHpAction != nullptr)
		changeHpAction(currentStatus.hp, currentStatus.maxHp);
}

void B_Reiana::Update(const float& deltaTime)
{
	fsm.Update(deltaTime);
	animator->Update(deltaTime);

	if (!dead&&reiana->GetHp()<=0)
	{
		fsm.ChangeState(B_ReianaStateType::Dash);
		dead = true;
	}
}

void B_Reiana::FixedUpdate(const float& deltaTime)
{
	fsm.FixedUpdate(deltaTime);
	rigidBody->FixedUpdate(deltaTime);
}

void B_Reiana::LateUpdate(const float& deltaTime)
{
	fsm.LateUpdate(deltaTime);
}

void B_Reiana::OnCollisionEnter(Collider* target)
{
}

void B_Reiana::OnCollisionStay(Collider* target)
{
}

void B_Reiana::OnCollisionEnd(Collider* target)
{
	if (target->GetColliderLayer() == ColliderLayer::Wall)
	{
		auto& targets = collider->GetCollisionTargets();
		bool isGround = false;
		for (auto& targetCollsion : targets)
		{
			if (targetCollsion == target)
				continue;

			Rectangle rect(collider->GetPosition(), collider->GetScale());
			Rectangle targetRect(targetCollsion->GetPosition(), targetCollsion->GetScale());

			if (rect.bottomPosition == targetRect.topPosition)
			{
				isGround = true;
				break;
			}
		}

		if (!isGround)
		{
			rigidBody->SetGround(false);
		}
	}
}
