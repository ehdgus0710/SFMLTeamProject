#include "stdafx.h"
#include "Reiana.h"
#include "Rigidbody.h"

#include "Collider.h"
#include "Animation.h"
#include "Animator.h"
#include "Player.h"

Reiana::Reiana(const std::string& name)
	:AnimationGameObject(name)
	,fsm(this)
{
	rigidBody = new Rigidbody(this);
	rigidBody->SetGround(false);
	CreateCollider(ColliderType::Rectangle, ColliderLayer::Reiana);


	animator->LoadCsv("animators/rayanna.csv");
	animator->ChangeAnimation("meteorAttack", false);

	currentStatus.hp = 100;
	currentStatus.maxHp = 100;
	// animator->CreateAnimation("ReianaIdle", "ReianaIdle", { 150, 192 }, 1, 0.1f, true);
}

Reiana::~Reiana()
{
}

void Reiana::TakeDamage(const DamegeInfo& damage)
{
	currentStatus.hp -= damage.damege;

	if (currentStatus.hp <= 0.f)
	{
		currentStatus.hp = 0.f;
		OnDead();
	}

	if (changeHpAction != nullptr)
		changeHpAction(currentStatus.hp, currentStatus.maxHp);
}

void Reiana::OnDead()
{
	// fsm.ChangeState(ReianaStateType::Dead);
}

void Reiana::Awake()
{
	AnimationGameObject::Awake();
}

void Reiana::Start()
{
	InputManager::GetInstance().BindKey(sf::Keyboard::Q);

	collider->SetOffsetPosition({ 0.f,-100.f });
	player = dynamic_cast<Player*>(SCENE_MANAGER.GetCurrentScene()->FindGameObject("Player", LayerType::Player));
	AnimationGameObject::Start();
	animator->ChangeAnimation("ReianaIdle", true);
	fsm.ChangeState(ReianaStateType::Idle);
	collider->SetScale({ 60.f,60.f });
	SetOrigin(Origins::BottomCenter);
	SetScale({ -3.5f,3.5f });

	if (changeHpAction != nullptr)
		changeHpAction(currentStatus.hp, currentStatus.maxHp);
}

void Reiana::Update(const float& deltaTime)
{
	fsm.Update(deltaTime);
	animator->Update(deltaTime);
	if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::Q))
	{
		fsm.ChangeState(ReianaStateType::Rising);
	}
	if (currentStatus.hp <= 0)
	{
		fsm.ChangeState(ReianaStateType::Dead);
	}
}

void Reiana::FixedUpdate(const float& deltaTime)
{
	fsm.FixedUpdate(deltaTime);
	rigidBody->FixedUpdate(deltaTime);
}

void Reiana::LateUpdate(const float& deltaTime)
{
	fsm.LateUpdate(deltaTime);
}

void Reiana::OnCollisionEnter(Collider* target)
{
}

void Reiana::OnCollisionStay(Collider* target)
{
}

void Reiana::OnCollisionEnd(Collider* target)
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

void Reiana::SetCount(int con)
{
	count = con;
}
