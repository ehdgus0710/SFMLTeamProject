#include "stdafx.h"
#include "Rigidbody.h"
#include "PhysicsManager.h"

Rigidbody::Rigidbody(GameObject* owner)
	: mass(1.f)
	, isGround(true)
	, dropSpeed(0.f)
	, maxDropSpeed(200.f)
	, owner(owner)
	, friction(false)
	, isActive(true)
	, prevDropSpeed(0.f)
{
}

Rigidbody::~Rigidbody()
{
}

void Rigidbody::SetVelocity(const sf::Vector2f& velocity)
{
	this->velocity = velocity;
}

void Rigidbody::AddVelocity(const sf::Vector2f& addVelocity)
{
	velocity += addVelocity;
}

void Rigidbody::AddForce(const sf::Vector2f& force)
{
	this->force += force * mass;
}

void Rigidbody::SetGround(bool isGround)
{
	this->isGround = isGround;
}

void Rigidbody::ResetVelocity()
{
	velocity = sf::Vector2f::zero;
}

void Rigidbody::ResetDropSpeed()
{
	dropSpeed = 0.f; 
}

void Rigidbody::FixedUpdate(const float& fixedDeltaTime)
{
	//velocity = accel * fixedDeltaTime;
	if (!isActive || fixedDeltaTime == 0.f)
		return;

	if (!isGround)
	{
		dropSpeed += Gravity.y * fixedDeltaTime * mass * 5.f;
		velocity.y += dropSpeed;

		prevDropSpeed = velocity.y * fixedDeltaTime;
	} 
	else
	{
		dropSpeed = 0.f;
		velocity.y = 0.f;
	}

	owner->SetPosition(owner->GetPosition() + velocity * fixedDeltaTime);
}
void Rigidbody::Awake()
{
}

void Rigidbody::Start()
{
}

bool Rigidbody::Save() const
{
	return false;
}

bool Rigidbody::Load()
{
	return false;
}

bool Rigidbody::SaveCsv(const std::string& filePath) const
{
	return false;
}

bool Rigidbody::LoadCsv(const std::string& filePath)
{
	return false;
}
