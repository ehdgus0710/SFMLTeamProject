#include "stdafx.h"
#include "TestPlayer.h"
#include "Animator.h"

TestPlayer::TestPlayer(const std::string& texId, const std::string& name)
	: SpriteGameObject(texId, name)
	, speed(500.f)
	, isJump(false)
{
}

TestPlayer::~TestPlayer()
{
	if (rigidBody != nullptr)
		delete rigidBody;
}

void TestPlayer::InputMove()
{
	/*moveDirection = sf::Vector2f::zero;

	if (InputManager::GetInstance().GetKeyPressed(sf::Keyboard::Left))
	{
		moveDirection.x += -1.f;
	}
	if (InputManager::GetInstance().GetKeyPressed(sf::Keyboard::Right))
	{
		moveDirection.x += 1.f;
	}*/
	if(rigidBody != nullptr)
		rigidBody->SetVelocity({ InputManager::GetInstance().GetAxis(Axis::Horizontal) * speed , rigidBody->GetCurrentVelocity().y});
}

void TestPlayer::InputJump()
{
	if (isJump)
		return;


	if (InputManager::GetInstance().GetKeyUp(sf::Keyboard::Space))
	{
		isJump = true;
		rigidBody->SetGround(false);
		rigidBody->SetVelocity({ rigidBody->GetCurrentVelocity().x, -500.f });

	}
	else if (InputManager::GetInstance().GetKeyPressed(sf::Keyboard::Space) && InputManager::GetInstance().GetAxis(Axis::Jump) == 1.f)
	{
		isJump = true;
		rigidBody->SetGround(false);
		rigidBody->SetVelocity({ rigidBody->GetCurrentVelocity().x, -800.f });
	}
}

void TestPlayer::Awake()
{
	rigidBody = new Rigidbody(this);
	rigidBody->SetGround(true);
}

void TestPlayer::Update(const float& deltaTime)
{
	if (animator)
		animator->Update(deltaTime);

	InputMove();

	InputJump();
}

void TestPlayer::FixedUpdate(const float& deltaTime)
{
	if(rigidBody != nullptr)
		rigidBody->FixedUpdate(deltaTime);

	if (isJump && position.y >= 0.f)
	{
		isJump = false;
		position.y = 0.f;

		rigidBody->SetGround(true);
		SetPosition(position);
	}
}

void TestPlayer::LateUpdate(const float& deltaTime)
{
}
