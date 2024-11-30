#include "stdafx.h"
#include "YggdrasilHead.h"

#include "Rigidbody.h"
#include "Animator.h"
#include "Collider.h"
#include "Animation.h"

#include "Player.h"

void YggdrasilHead::Awake()
{
	AnimationGameObject::Awake();
}

void YggdrasilHead::Start()
{
	AnimationGameObject::Start();
}

void YggdrasilHead::Update(const float& deltaTime)
{
	rigidBody->Update(deltaTime);
}

void YggdrasilHead::FixedUpdate(const float& deltaTime)
{
	rigidBody->FixedUpdate(deltaTime);
}

void YggdrasilHead::LateUpdate(const float& deltaTime)
{
}

void YggdrasilHead::OnCollisionEnter(Collider* target)
{
}

void YggdrasilHead::OnCollisionStay(Collider* target)
{
}

void YggdrasilHead::OnCollisionEnd(Collider* target)
{
}

void YggdrasilHead::fire()
{
}

void YggdrasilHead::SetYggdrasil(Yggdrasil* player)
{
}

void YggdrasilHead::SetPlayer(Player* player)
{
	this->player = player;

}

YggdrasilHead::YggdrasilHead(const std::string& name)
	: AnimationGameObject(name)
{
	rigidBody = new Rigidbody(this);
	rigidBody->SetGround(false);
	CreateCollider(ColliderType::Rectangle, ColliderLayer::Enemy, sf::Vector2f::zero, sf::Vector2f(100.f, 100.f));
}

YggdrasilHead::~YggdrasilHead()
{
}
