#include "stdafx.h"
#include "Head.h"

#include "Rigidbody.h"
#include "Animator.h"
#include "Collider.h"
#include "Animation.h"

#include "Player.h"
#include "Enemy.h"
#include "Yggdrasil.h"
#include "Reiana.h"

Head::Head(const std::string& name)
	: SpriteGameObject("SkulHead", name)
	, isThrow(false)
	, skill1OnTime(0.5f)
	, player(nullptr)
	, moveDirectionX(0)
	, currentTime(0.f)
	, onSkill(false)
{
	rigidBody = new Rigidbody(this);
	rigidBody->SetGround(false);
	CreateCollider(ColliderType::Rectangle, ColliderLayer::PlayerHead);
	scale = { 3.f, 3.f };

	damageInfo.damege = 15.f;
	damageInfo.owner = this;
}

Head::~Head()
{
}
void Head::Awake()
{
	SpriteGameObject::Awake();
}

void Head::Start()
{
	TEXTURE_MANAGER.Load("SkulHead", "graphics/skul/SkulHead.png");
	SpriteGameObject::Start();
	
}

void Head::SetRotation(float angle)
{
	rotation = angle;
	sprite.setRotation(rotation);
}

void Head::Update(const float& deltaTime)
{
	if (isThrow)
	{
		currentTime += deltaTime;

		if (currentTime >= skill1OnTime)
			EndThrow();
		else
		{
			SetPosition(sf::Vector2f::Lerp(skill1StartPos, skillEndPos, currentTime / skill1OnTime));
			SetRotation(Utils::Lerp(0.f, 360.f, currentTime / skill1OnTime));
		}

	}
}

void Head::FixedUpdate(const float& deltaTime)
{
	rigidBody->FixedUpdate(deltaTime);
}

void Head::LateUpdate(const float& deltaTime)
{
}

void Head::OnCollisionEnter(Collider* target)
{
	if (target->GetColliderLayer() == ColliderLayer::Wall)
	{
		if (isThrow)
			EndThrow();
		else
			rigidBody->ResetVelocity();
	}
	else if ((target->GetColliderLayer() == ColliderLayer::Enemy || target->GetColliderLayer() == ColliderLayer::Boss 
		|| target->GetColliderLayer() == ColliderLayer::Yggdrasil || target->GetColliderLayer() == ColliderLayer::Reiana) && isThrow)
	{
		if (target->GetColliderLayer() == ColliderLayer::Enemy)
		{
			((Enemy*)target->GetOwner())->TakeDamage(damageInfo);
		}
		else if (target->GetColliderLayer() == ColliderLayer::Boss)
		{
			Yggdrasil* yggdrasil = dynamic_cast<Yggdrasil*>(target->GetOwner());

			if (yggdrasil)
				yggdrasil->TakeDamage(damageInfo);
			else if (dynamic_cast<Reiana*>(target->GetOwner()))
				static_cast<Reiana*>(target->GetOwner())->TakeDamage(damageInfo);
		}
		else if (target->GetColliderLayer() == ColliderLayer::Yggdrasil)
		{
			static_cast<Yggdrasil*>(target->GetOwner())->TakeDamage(damageInfo);
		}
		else if (target->GetColliderLayer() == ColliderLayer::Reiana)
		{
			static_cast<Reiana*>(target->GetOwner())->TakeDamage(damageInfo);
		}
		EndThrow();
	}
}

void Head::OnCollisionStay(Collider* target)
{
}

void Head::OnCollisionEnd(Collider* target)
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

void Head::ThrowHead()
{
	isThrow = true;
	onSkill = true;

	skill1StartPos = player->GetPosition();
	skillEndPos = skill1StartPos + (player->IsFlipX() ? sf::Vector2f::left : sf::Vector2f::right) * 800.f;

	if (player->IsFlipX() && scale.x > 0.f || !player->IsFlipX() && scale.x < 0.f)
	{
		scale.x = scale.x * -1.f;
	}

	SetScale(scale);

	rigidBody->SetActive(false);
	currentTime = 0.f;
}

void Head::EndThrow()
{
	rigidBody->SetActive(true);
	rigidBody->SetGround(false);
	rigidBody->ResetDropSpeed();
	rigidBody->ResetVelocity();
	rigidBody->SetVelocity({ Utils::RandomRange(-50.f, 50.f), Utils::RandomRange(-800.f, -400.f) });
	isThrow = false;
	onSkill = false;
}

void Head::SetPlayer(Player* player)
{
	this->player = player;
}

PlayerSaveData Head::GetPlayerSaveData() const
{
	return PlayerSaveData();
}

void Head::LoadData(const PlayerSaveData& data)
{
}

