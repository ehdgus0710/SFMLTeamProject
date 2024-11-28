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
	CreateCollider(ColliderType::Rectangle, ColliderLayer::Player);

	animator->CreateAnimation("ReianaIdle", "ReianaIdle", { 150, 192 }, 1, 0.1f, true);
}

Reiana::~Reiana()
{
}

void Reiana::Awake()
{
	AnimationGameObject::Awake();
}

void Reiana::Start()
{
	InputManager::GetInstance().BindKey(sf::Keyboard::Numpad1);
	InputManager::GetInstance().BindKey(sf::Keyboard::Numpad2);
	InputManager::GetInstance().BindKey(sf::Keyboard::Numpad3);
	InputManager::GetInstance().BindKey(sf::Keyboard::Numpad4);

	player = dynamic_cast<Player*>(SCENE_MANAGER.GetCurrentScene()->FindGameObject("Player", LayerType::Player));
	AnimationGameObject::Start();
	animator->ChangeAnimation("ReianaIdle", true);
	fsm.ChangeState(ReianaStateType::Idle);
	collider->SetScale({ 150.f,192.f });

}

void Reiana::Update(const float& deltaTime)
{
	fsm.Update(deltaTime);
	animator->Update(deltaTime);
	if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::Numpad1))
	{
		fsm.ChangeState(ReianaStateType::DropAttack);
	}
	if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::Numpad2))
	{
		fsm.ChangeState(ReianaStateType::GroundAttack);
	}
	if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::Numpad3))
	{
		fsm.ChangeState(ReianaStateType::Dimension);
	}
	if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::Numpad4))
	{
		fsm.ChangeState(ReianaStateType::Knife);
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
