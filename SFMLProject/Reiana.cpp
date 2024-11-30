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


	animator->LoadCsv("animators/rayanna.csv");
	animator->ChangeAnimation("meteorAttack", false);

	// animator->CreateAnimation("ReianaIdle", "ReianaIdle", { 150, 192 }, 1, 0.1f, true);
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
	InputManager::GetInstance().BindKey(sf::Keyboard::Q);
	InputManager::GetInstance().BindKey(sf::Keyboard::W);
	InputManager::GetInstance().BindKey(sf::Keyboard::E);
	InputManager::GetInstance().BindKey(sf::Keyboard::R);
	InputManager::GetInstance().BindKey(sf::Keyboard::T);
	InputManager::GetInstance().BindKey(sf::Keyboard::Y);


	player = dynamic_cast<Player*>(SCENE_MANAGER.GetCurrentScene()->FindGameObject("Player", LayerType::Player));
	AnimationGameObject::Start();
	animator->ChangeAnimation("ReianaIdle", true);
	fsm.ChangeState(ReianaStateType::Idle);
	collider->SetScale({ 150.f,192.f });
	SetOrigin(Origins::BottomCenter);
}

void Reiana::Update(const float& deltaTime)
{
	fsm.Update(deltaTime);
	animator->Update(deltaTime);
	if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::Q))
	{
		fsm.ChangeState(ReianaStateType::DropAttack);
	}
	if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::W))
	{
		fsm.ChangeState(ReianaStateType::GroundAttack);
	}
	if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::E))
	{
		fsm.ChangeState(ReianaStateType::Dimension);
	}
	if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::R))
	{
		fsm.ChangeState(ReianaStateType::ThreeSword);
	}
	if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::T))
	{
		fsm.ChangeState(ReianaStateType::Dash);
	}
	if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::Y))
	{
		fsm.ChangeState(ReianaStateType::Rising);
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
