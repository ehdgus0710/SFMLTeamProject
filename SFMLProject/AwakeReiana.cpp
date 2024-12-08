#include "stdafx.h"
#include "AwakeReiana.h"
#include "Rigidbody.h"

#include "Collider.h"
#include "Animation.h"
#include "Animator.h"
#include "Player.h"
#include "ReianaUIHub.h"

AwakeReiana::AwakeReiana(const std::string& name)
	:AnimationGameObject(name)
	, fsm(this)
{
	rigidBody = new Rigidbody(this);
	rigidBody->SetGround(false);
	CreateCollider(ColliderType::Rectangle, ColliderLayer::Reiana);


	animator->LoadCsv("animators/awakenRayanna.csv");
	animator->ChangeAnimation("meteorAttack", false);

	currentStatus.hp = 100;
	currentStatus.maxHp = 100;
	// animator->CreateAnimation("AwakeReianaIdle", "AwakeReianaIdle", { 150, 192 }, 1, 0.1f, true);
}

AwakeReiana::~AwakeReiana()
{
}

void AwakeReiana::TakeDamage(const DamegeInfo& damage)
{
	currentStatus.hp -= damage.damege;

	if (!dead&&currentStatus.hp <= 0.f)
	{
		currentStatus.hp = 0.f;
		OnDead();
		dead = true;
	}

	if (changeHpAction != nullptr)
		changeHpAction(currentStatus.hp, currentStatus.maxHp);
}

void AwakeReiana::OnDead()
{
	fsm.ChangeState(AwakeReianaStateType::Dead);
}

void AwakeReiana::Awake()
{
	AnimationGameObject::Awake();
}

void AwakeReiana::Start()
{
	InputManager::GetInstance().BindKey(sf::Keyboard::Q);

	collider->SetOffsetPosition({ 0.f,-100.f });
	player = dynamic_cast<Player*>(SCENE_MANAGER.GetCurrentScene()->FindGameObject("Player", LayerType::Player));
	AnimationGameObject::Start();
	animator->ChangeAnimation("awakenReianaIdle", true);
	fsm.ChangeState(AwakeReianaStateType::Awake);
	collider->SetScale({ 60.f,60.f });
	SetOrigin(Origins::BottomCenter);
	SetScale({ -3.5f,3.5f });
	OnFlipX();

	reianaUIHub->ChangePhase();
	if (changeHpAction != nullptr)
		changeHpAction(currentStatus.hp, currentStatus.maxHp);
}

void AwakeReiana::Update(const float& deltaTime)
{
	fsm.Update(deltaTime);
	animator->Update(deltaTime);
	if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::Q))
	{
		fsm.ChangeState(AwakeReianaStateType::DropAttack);
	}
}

void AwakeReiana::FixedUpdate(const float& deltaTime)
{
	fsm.FixedUpdate(deltaTime);
	rigidBody->FixedUpdate(deltaTime);
}

void AwakeReiana::LateUpdate(const float& deltaTime)
{
	fsm.LateUpdate(deltaTime);
}

void AwakeReiana::OnCollisionEnter(Collider* target)
{
}

void AwakeReiana::OnCollisionStay(Collider* target)
{
}

void AwakeReiana::OnCollisionEnd(Collider* target)
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

void AwakeReiana::SetCount(int con)
{
	count = con;
}
