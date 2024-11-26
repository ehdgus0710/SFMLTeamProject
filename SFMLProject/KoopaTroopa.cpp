#include "stdafx.h"
#include "KoopaTroopa.h"

#include "Animator.h"
#include "Collider.h"
#include "Rigidbody.h"
#include "Player.h"
#include "Animation.h"
#include "KoopaTroopaFSM.h"
#include "BlockObject.h"
#include "BrickBlockObject.h"

KoopaTroopa::KoopaTroopa(const std::string& name)
	: Enemy(EnemyType::KoopaTroopa, name)
{
	fsm = new KoopaTroopaFSM(this);

	CreateAnimator();
	animator->LoadCsv("animators/koopaTroopa.csv");
	CreateCollider(ColliderType::Rectangle, ColliderLayer::Enemy);
}

KoopaTroopa::~KoopaTroopa()
{
	if (fsm != nullptr)
	{
		delete fsm;
	}
}

void KoopaTroopa::Awake()
{
	animator->ChangeAnimation("koopaTroopaScout", true);
}

void KoopaTroopa::Start()
{
	Enemy::Start();

	fsm->ChangeState(EnemyStateType::Scout);


	GetCollider()->SetScale({ 64.f, 64.f });
	// GetCollider()->SetScale({ (sf::Vector2f)animator->GetCurrentAnimation()->GetFrameInfo()[0].rectSize });
}

void KoopaTroopa::OnCollisionEnter(Collider* target)
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
			if (currentState == EnemyStateType::Scout)
			{
				sf::Vector2f targetPosition = target->GetPosition();

				Rectangle rect(collider->GetPosition(), collider->GetScale());
				Rectangle targetRect(targetPosition, target->GetScale());
				float prevPositionY = (target->GetOwner()->GetRigidbody()->GetCurrentVelocity().y + target->GetOwner()->GetRigidbody()->GetCurrentDropSpeed()) * TimeManager::GetInstance().GetFixedDeletaTime() * player->GetSpeed();

				if (rect.topPosition > targetRect.bottomPosition - prevPositionY)
				{
					fsm->ChangeState(EnemyStateType::Groggy);
					player->GetRigidbody()->ResetDropSpeed();
					player->GetRigidbody()->SetVelocity({ player->GetRigidbody()->GetCurrentVelocity().x, -350.f });
					player->GetFSM().ChangeState(PlayerStateType::Jump);

					SoundManger::GetInstance().PlaySfx("Chop");
				}
				else if (rect.bottomPosition < targetRect.topPosition - prevPositionY)
					player->TakeDamage();
				else
					player->TakeDamage();


				return;
			}
			else if (currentState == EnemyStateType::Groggy)
			{
				sf::Vector2f targetPosition = target->GetPosition();
				float direction = targetPosition.x - position.x;

				if (direction < 0.f)
				{
					moveDirection.x = 1.f;
				}
				else
					moveDirection.x = -1.f;

				fsm->ChangeState(EnemyStateType::Move);
				SoundManger::GetInstance().PlaySfx("Kick");
			}
			else if (currentState == EnemyStateType::Move)
			{
				sf::Vector2f targetPosition = target->GetPosition();

				Rectangle rect(collider->GetPosition(), collider->GetScale());
				Rectangle targetRect(targetPosition, target->GetScale());
				float prevPositionY = (target->GetOwner()->GetRigidbody()->GetCurrentVelocity().y + target->GetOwner()->GetRigidbody()->GetCurrentDropSpeed()) * TimeManager::GetInstance().GetFixedDeletaTime() * player->GetSpeed();

				if (rect.topPosition > targetRect.bottomPosition - prevPositionY)
				{
					float direction = targetPosition.x - position.x;

					if (direction < 0.f)
					{
						moveDirection.x = 1.f;
					}
					else
						moveDirection.x = -1.f;

					fsm->ChangeState(EnemyStateType::Move);

					SoundManger::GetInstance().PlaySfx("Chop");
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

		
		
	}
	else if (target->GetColliderLayer() == ColliderLayer::Wall || target->GetColliderLayer() == ColliderLayer::Enemy
		|| target->GetColliderLayer() == ColliderLayer::Block)
	{
		sf::Vector2f targetPosition = target->GetPosition();

		Rectangle rect(collider->GetPosition(), collider->GetScale());
		Rectangle targetRect(targetPosition, target->GetScale());

		if (currentState == EnemyStateType::Scout)
		{
			if (rect.bottomPosition != targetRect.topPosition)
			{
				moveDirection.x *= -1.f;
				fsm->ChangeState(EnemyStateType::Scout);
			}
		}
		if (currentState == EnemyStateType::Move)
		{
			if (!(rect.topPosition > targetRect.bottomPosition && rect.bottomPosition < targetRect.topPosition))
			{

				if (target->GetColliderLayer() == ColliderLayer::Enemy)
					((Enemy*)target->GetOwner())->TakeDamage();
				else if (target->GetColliderLayer() == ColliderLayer::Block)
				{
					if(((BlockObject*)target->GetOwner())->GetBlockType() == BlockType::Brick)
					{
						((BrickBlockObject*)target->GetOwner())->OnBreak();
					}
					else
					{
						moveDirection.x *= -1.f;
						fsm->ChangeState(EnemyStateType::Move);
					}

				}
				else
				{
					moveDirection.x *= -1.f;
					fsm->ChangeState(EnemyStateType::Move);
				}

			}
		}
		//fsm->ChangeState(EnemyStateType::Scout);
	}
}

void KoopaTroopa::OnCollisionStay(Collider* target)
{
}

void KoopaTroopa::OnCollisionEnd(Collider* target)
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