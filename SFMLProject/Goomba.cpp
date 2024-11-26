#include "stdafx.h"
#include "Goomba.h"

#include "Animator.h"
#include "Animation.h"
#include "Collider.h"
#include "Collision.h"
#include "Player.h"
#include "Rigidbody.h"
#include "PlayerFSM.h"

Goomba::Goomba(const std::string& name)
	: Enemy(EnemyType::Goomba, name)
{
	fsm = new GoombaFSM(this);

	CreateAnimator();
	animator->LoadCsv("animators/goomba.csv");
	CreateCollider(ColliderType::Rectangle, ColliderLayer::Enemy);
}

Goomba::~Goomba()
{
	if (fsm != nullptr)
	{
		delete fsm;
	}
}

void Goomba::Awake()
{
	// animator->ChangeAnimation("goombaMove", true);
}

void Goomba::Start()
{
	Enemy::Start();

	fsm->ChangeState(EnemyStateType::Scout);

	GetCollider()->SetScale({ (sf::Vector2f)animator->GetCurrentAnimation()->GetFrameInfo()[0].rectSize });
}

void Goomba::OnCollisionEnter(Collider* target)
{
	if (target->GetColliderLayer() == ColliderLayer::Player)
	{
		Player* player = (Player*)target->GetOwner();
		
		if (player->IsStarState())
		{
			SetHitDirection(position.x < player->GetPosition().x ? sf::Vector2f::left : sf::Vector2f::right);
			TakeDamage();
		}
		else
		{
			sf::Vector2f targetPosition = target->GetPosition();

			Rectangle rect(collider->GetPosition(), collider->GetScale());
			Rectangle targetRect(targetPosition, target->GetScale());
			float prevPositionY = (target->GetOwner()->GetRigidbody()->GetCurrentVelocity().y + target->GetOwner()->GetRigidbody()->GetCurrentDropSpeed()) * TimeManager::GetInstance().GetFixedDeletaTime() * player->GetSpeed();

			if (rect.topPosition > targetRect.bottomPosition - prevPositionY)
			{
				OnJumpDead();
				TakeDamage();
				player->GetRigidbody()->ResetDropSpeed();
				player->GetRigidbody()->SetVelocity({ player->GetRigidbody()->GetCurrentVelocity().x, -350.f });
				player->GetFSM().ChangeState(PlayerStateType::Jump);
			}
			else if (rect.bottomPosition < targetRect.topPosition - prevPositionY)
				player->TakeDamage();
			else
				player->TakeDamage();
		}
	}
	else if (target->GetColliderLayer() == ColliderLayer::Wall || target->GetColliderLayer() == ColliderLayer::Block)
	{
		sf::Vector2f targetPosition = target->GetPosition();

		Rectangle rect(collider->GetPosition(), collider->GetScale());
		Rectangle targetRect(targetPosition, target->GetScale());
		float prevPositionY = (rigidBody->GetCurrentVelocity().y + rigidBody->GetCurrentDropSpeed()) * TimeManager::GetInstance().GetFixedDeletaTime();

		// if (!(rect.topPosition < targetRect.bottomPosition - prevPositionY && rect.bottomPosition > targetRect.topPosition - prevPositionY))

 		if (rect.bottomPosition != targetRect.topPosition)
		{
			moveDirection.x *= -1.f;
			fsm->ChangeState(EnemyStateType::Scout);
		}

	}
	else if (target->GetColliderLayer() == ColliderLayer::Enemy)
	{
		sf::Vector2f targetPosition = target->GetPosition();

		Rectangle rect(collider->GetPosition(), collider->GetScale());
		Rectangle targetRect(targetPosition, target->GetScale());
		float prevPositionY = (rigidBody->GetCurrentVelocity().y + rigidBody->GetCurrentDropSpeed()) * TimeManager::GetInstance().GetFixedDeletaTime();

		// if (!(rect.topPosition < targetRect.bottomPosition - prevPositionY && rect.bottomPosition > targetRect.topPosition - prevPositionY))

		if ((!(rect.topPosition > targetRect.bottomPosition && rect.bottomPosition <= targetRect.topPosition)))
		{
			moveDirection.x *= -1.f;
			fsm->ChangeState(EnemyStateType::Scout);
		}
	}
}

void Goomba::OnCollisionStay(Collider* target)
{
	/*if (target->GetColliderLayer() == ColliderLayer::Wall || target->GetColliderLayer() == ColliderLayer::Enemy
		|| target->GetColliderLayer() == ColliderLayer::Block)
	{
		sf::Vector2f targetPosition = target->GetPosition();

		Rectangle rect(collider->GetPosition(), collider->GetScale());
		Rectangle targetRect(targetPosition, target->GetScale());

		if (!(rect.topPosition > targetRect.bottomPosition && rect.bottomPosition < targetRect.topPosition))
		{
			moveDirection.x *= -1.f;
			fsm->ChangeState(EnemyStateType::Scout);
		}

	}*/
}

void Goomba::OnCollisionEnd(Collider* target)
{
	if (target->GetColliderLayer() == ColliderLayer::Wall || target->GetColliderLayer() == ColliderLayer::Block)
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
			rigidBody->SetGround(false);
		else
			rigidBody->SetGround(true);

	}
}
