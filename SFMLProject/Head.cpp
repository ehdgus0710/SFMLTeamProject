#include "stdafx.h"
#include "Head.h"

#include "Rigidbody.h"
#include "Animator.h"
#include "Collider.h"
#include "Animation.h"

#include "GameManager.h"
#include "Camera.h"
#include "InGameScoreUI.h"

#include "Player.h"

Head::Head(const std::string& name)
	: AnimationGameObject(name)
	, isThrow(false)
	, skill1OnTime(0.2f)
	, player(nullptr)
	, moveDirectionX(0)
	, currentTime(0.f)
{
	rigidBody = new Rigidbody(this);
	rigidBody->SetGround(false);
	CreateCollider(ColliderType::Rectangle, ColliderLayer::Player, sf::Vector2f(10.f, 10.f), sf::Vector2f(1.5f, 1.5f));
}

Head::~Head()
{
}
void Head::Awake()
{
	AnimationGameObject::Awake();
}

void Head::Start()
{
	AnimationGameObject::Start();
	
}

void Head::Update(const float& deltaTime)
{
	if (isThrow)
	{
		currentTime += deltaTime;

		if (currentTime >= skill1OnTime)
		{
			rigidBody->SetActive(true);
			rigidBody->SetGround(false);
			rigidBody->ResetDropSpeed();
			rigidBody->ResetVelocity();
			rigidBody->SetVelocity({ Utils::RandomRange(-50.f, 50.f), Utils::RandomRange(-800.f, -400.f)});
			isThrow = false;
		}
		else
			SetPosition(sf::Vector2f::Lerp(skill1StartPos, skillEndPos, currentTime / skill1OnTime));

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
	if(target->GetColliderLayer() == ColliderLayer::Wall)
		rigidBody->ResetVelocity();
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

	skill1StartPos = player->GetPosition();
	skillEndPos = skill1StartPos + (player->IsFlipX() ? sf::Vector2f::left : sf::Vector2f::right) * 800.f;
	rigidBody->SetActive(false);
	currentTime = 0.f;
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

