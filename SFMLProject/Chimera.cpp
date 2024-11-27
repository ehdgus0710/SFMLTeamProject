#include "stdafx.h"
#include "Chimera.h"
#include "Rigidbody.h"

#include "Collider.h"
#include "Animation.h"
#include "Animator.h"

Chimera::Chimera(const std::string& name)
	:AnimationGameObject(name)
	,fsm(this)
{
	rigidBody = new Rigidbody(this);
	rigidBody->SetGround(false);
	CreateCollider(ColliderType::Rectangle, ColliderLayer::Player);

	animator->CreateAnimation("ChimeraIdle", "chimeraIdle", { 1000, 757 }, 1, 0.1f, true);
}

Chimera::~Chimera()
{
}

void Chimera::Awake()
{
	AnimationGameObject::Awake();
}

void Chimera::Start()
{
	AnimationGameObject::Start();
	animator->ChangeAnimation("ChimeraIdle", true);
	fsm.ChangeState(ChimeraStateType::GroundAttack);
	collider->SetScale({ 1000.f,750.f });
}

void Chimera::Update(const float& deltaTime)
{
	fsm.Update(deltaTime);
	animator->Update(deltaTime);
}

void Chimera::FixedUpdate(const float& deltaTime)
{
	fsm.FixedUpdate(deltaTime);
	rigidBody->FixedUpdate(deltaTime);
}

void Chimera::LateUpdate(const float& deltaTime)
{
	fsm.LateUpdate(deltaTime);
}

void Chimera::OnCollisionEnter(Collider* target)
{
}

void Chimera::OnCollisionStay(Collider* target)
{
}

void Chimera::OnCollisionEnd(Collider* target)
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
