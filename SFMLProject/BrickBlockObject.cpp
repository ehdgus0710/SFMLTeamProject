#include "stdafx.h"
#include "BrickBlockObject.h"
#include "Collider.h"
#include "Player.h"
#include "Rigidbody.h"
#include "Enemy.h"
#include "BrickBlockParticle.h"

BrickBlockObject::BrickBlockObject(const std::string& texId, const std::string& name)
	: BlockObject(BlockType::Brick, texId, name)
	, isHit(false)
	, hitMoveDistance(32.f)
	, moveSpeed(500.f)
	, isReturn(false)
	, currentMoveTime(0.f)
{
}

void BrickBlockObject::OnBreak()
{
	SetDestory(true);
}

void BrickBlockObject::OnHitMove()
{
	if (!isHit)
	{
		isHit = true;
		startPosition = position;
		endPosition = position;
		endPosition.y -= hitMoveDistance;
		currentMoveTime = 0.f;
	}

	isReturn = false;
}

void BrickBlockObject::Update(const float& deltaTime)
{
	if (isHit)
	{
		position.y += moveSpeed * deltaTime * (isReturn ? 1.f : -1.f);
		// currentMoveTime += deltaTime;

		if (!isReturn)
		{
			if (position.y <= endPosition.y)
			{
				position.y = endPosition.y;
				isReturn = true;
			}
		}
		else
		{
			if (position.y >= startPosition.y)
			{
				position.y = startPosition.y;
				isHit = false;
			}
		}

		SetPosition(position);
	}
}

void BrickBlockObject::OnCollisionEnter(Collider* target)
{
	if (target->GetColliderLayer() == ColliderLayer::Player)
	{
		player = (Player*)target->GetOwner();

		sf::Vector2f targetPosition = target->GetPosition();

		Rectangle rect(collider->GetPosition(), collider->GetScale());
		Rectangle targetRect(targetPosition, target->GetScale());
		float prevPositionY = player->GetRigidbody()->GetPrevDropSpeed();

		if (rect.topPosition > targetRect.bottomPosition - prevPositionY)
		{
			player->GetRigidbody()->SetGround(true);
			player->SetPosition({ targetPosition.x , rect.topPosition - target->GetScale().y * 0.5f });
		}
		else if (rect.bottomPosition < targetRect.topPosition - prevPositionY)
		{
			player->SetPosition({ player->GetPosition().x, rect.bottomPosition + target->GetScale().y * 0.5f });
			player->GetRigidbody()->SetVelocity({ player->GetRigidbody()->GetCurrentVelocity().x , 0.f });

			if (abs(position.x - player->GetPosition().x) < 28.f)
			{
				auto targets = collider->GetCollisionTargets();

				for (auto& target : targets)
				{
					Enemy* enemy = dynamic_cast<Enemy*>(target->GetOwner());
					if (enemy != nullptr)
					{
						enemy->SetHitDirection(enemy->GetPosition().x < position.x ? sf::Vector2f::left : sf::Vector2f::right);
						enemy->TakeDamage();
					}
				}
				if (player->GetCurrentHP() == 1)
				{
					OnHitMove();
					SoundManger::GetInstance().PlaySfx("Bump");
				}
				else
				{
					SetDestory(true);

					Scene* currentScene = SceneManager::GetInstance().GetCurrentScene();
					for (int i = 0; i < 2; ++i)
					{
						BrickBlockParticle* particle = currentScene->AddGameObject(new BrickBlockParticle({ 64, 32, 16, 16 }, "Items"), LayerType::BackGround);
						particle->SetPosition(position);
						particle->SetMoveDirection(i != 0 ? sf::Vector2f::left : sf::Vector2f::right);
						particle->StartMove((i + 1) * -600.f);
						particle->Start();
					}
					for (int i = 0; i < 2; ++i)
					{
						BrickBlockParticle* particle = currentScene->AddGameObject(new BrickBlockParticle({ 64, 16, 16, 16 }, "Items"), LayerType::BackGround);
						particle->SetPosition(position);
						particle->SetMoveDirection(i != 0 ? sf::Vector2f::right : sf::Vector2f::left);
						particle->StartMove((i + 1) * -600.f);
						particle->Start();
					}

					SoundManger::GetInstance().PlaySfx("BrickSmash");
				}
			}
			else
				SoundManger::GetInstance().PlaySfx("Bump");

		}
	}
	else if (target->GetColliderLayer() == ColliderLayer::Enemy || target->GetColliderLayer() == ColliderLayer::Item)
	{
		GameObject* object = target->GetOwner();

		sf::Vector2f targetPosition = target->GetPosition();

		Rectangle rect(collider->GetPosition(), collider->GetScale());
		Rectangle targetRect(targetPosition, target->GetScale());
		float prevPositionY = object->GetRigidbody()->GetCurrentVelocity().y * TimeManager::GetInstance().GetFixedDeletaTime();

		if (rect.topPosition > targetRect.bottomPosition - prevPositionY)
		{
			object->GetRigidbody()->SetGround(true);
			object->SetPosition({ targetPosition.x , rect.topPosition - target->GetScale().y * 0.5f });
		}
	}
}

void BrickBlockObject::OnCollisionStay(Collider* target)
{
	if (target->GetColliderLayer() == ColliderLayer::Player)
	{
		Rigidbody* targetRigidbody = player->GetRigidbody();

		Rectangle rect(collider->GetPosition(), collider->GetScale());
		Rectangle targetRect(target->GetPosition(), target->GetScale());

		sf::Vector2f prevPosition = player->GetRigidbody()->GetCurrentVelocity() * TimeManager::GetInstance().GetFixedDeletaTime();


		if (rect.topPosition == targetRect.bottomPosition)
		{
			if (rect.leftPosition > targetRect.leftPosition && rect.leftPosition < targetRect.rightPosition)
				targetRigidbody->SetVelocity({ 0.f, targetRigidbody->GetCurrentVelocity().y });
			else if (rect.rightPosition < targetRect.rightPosition && rect.rightPosition >(targetRect.leftPosition))
				targetRigidbody->SetVelocity({ 0.f, targetRigidbody->GetCurrentVelocity().y });
		}
		else
		{
			if (rect.bottomPosition > targetRect.topPosition)
			{
				if (rect.leftPosition > targetRect.leftPosition && rect.leftPosition < targetRect.rightPosition)
				{
					player->SetPosition({ rect.leftPosition - target->GetScale().x * 0.5f, player->GetPosition().y });
					targetRigidbody->SetVelocity({ 0.f, targetRigidbody->GetCurrentVelocity().y });
				}
				else if (rect.rightPosition < targetRect.rightPosition && rect.rightPosition >(targetRect.leftPosition))
				{
					player->SetPosition({ rect.rightPosition + target->GetScale().x * 0.5f, player->GetPosition().y });
					targetRigidbody->SetVelocity({ 0.f, targetRigidbody->GetCurrentVelocity().y });
				}
			}
		}
	}
	else if (target->GetColliderLayer() == ColliderLayer::Enemy || target->GetColliderLayer() == ColliderLayer::Item)
	{
		GameObject* object = target->GetOwner();
		Rigidbody* targetRigidbody = target->GetOwner()->GetRigidbody();

		Rectangle rect(collider->GetPosition(), collider->GetScale());
		Rectangle targetRect(target->GetPosition(), target->GetScale());

		if (rect.topPosition == targetRect.bottomPosition)
		{
			if (rect.leftPosition > targetRect.leftPosition && rect.leftPosition < targetRect.rightPosition)
				targetRigidbody->SetVelocity({ 0.f, targetRigidbody->GetCurrentVelocity().y });
			else if (rect.rightPosition < targetRect.rightPosition && rect.rightPosition >(targetRect.leftPosition))
				targetRigidbody->SetVelocity({ 0.f, targetRigidbody->GetCurrentVelocity().y });
		}
		else
		{
			if (rect.bottomPosition > targetRect.topPosition)
			{
				if (rect.leftPosition > targetRect.leftPosition && rect.leftPosition < targetRect.rightPosition)
				{
					object->SetPosition({ rect.leftPosition - target->GetScale().x * 0.5f, object->GetPosition().y });
					targetRigidbody->SetVelocity({ 0.f, targetRigidbody->GetCurrentVelocity().y });
				}
				else if (rect.rightPosition < targetRect.rightPosition && rect.rightPosition >(targetRect.leftPosition))
				{
					object->SetPosition({ rect.rightPosition + target->GetScale().x * 0.5f, object->GetPosition().y });
					targetRigidbody->SetVelocity({ 0.f, targetRigidbody->GetCurrentVelocity().y });
				}
			}
		}
	}

	/*if (target->GetColliderLayer() == ColliderLayer::Wall || target->GetColliderLayer() == ColliderLayer::Enemy
		|| target->GetColliderLayer() == ColliderLayer::Block)
	{

	}*/
}

void BrickBlockObject::OnCollisionEnd(Collider* target)
{
}

bool BrickBlockObject::Save() const
{
	return false;
}

bool BrickBlockObject::Load()
{
	return false;
}