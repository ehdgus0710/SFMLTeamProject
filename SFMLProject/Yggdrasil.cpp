#include "stdafx.h"
#include "Yggdrasil.h"

#include "Rigidbody.h"
#include "Animator.h"
#include "Collider.h"
#include "Animation.h"

#include "GameManager.h"
#include "Camera.h"
#include "InGameScoreUI.h"
#include "YggdrasilBaseState.h"
#include "YggdrasilBody.h"
#include "YggdrasilHead.h"
#include "YggdrasilLeftHand.h"
#include "YggdrasilRightHand.h"
#include "YggdrasilEnergyBallBig.h"
#include "Player.h"

void Yggdrasil::Awake()
{
	AnimationGameObject::Awake();
}

void Yggdrasil::Start()
{
	AnimationGameObject::Start();

	InputManager::GetInstance().BindKey(sf::Keyboard::Numpad7);
	InputManager::GetInstance().BindKey(sf::Keyboard::Numpad8);
	InputManager::GetInstance().BindKey(sf::Keyboard::Numpad9);

	yggdrasilHead = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new YggdrasilHead("YggdrasilHead"), LayerType::Boss);
	yggdrasilHead->SetYggdrasil(this);
	yggdrasilHead->SetPosition({ 0.f, -600.f });
	yggdrasilHead->Awake();
	yggdrasilHead->GetCollider()->SetScale({ 200.f,200.f });
	yggdrasilHead->GetRigidbody()->SetActive(false);

	yggdrasilLeftHand = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new YggdrasilLeftHand("yggdrasilLeftHand"), LayerType::Boss);
	yggdrasilLeftHand->SetYggdrasil(this);
	yggdrasilLeftHand->SetPosition({ 450.f, -350.f });
	yggdrasilLeftHand->Awake();
	yggdrasilLeftHand->GetCollider()->SetScale({ 200.f,200.f });
	yggdrasilLeftHand->GetRigidbody()->SetActive(false);

	yggdrasilRightHand = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new YggdrasilRightHand("YggdrasilRightHand"), LayerType::Boss);
	yggdrasilRightHand->SetYggdrasil(this);
	yggdrasilRightHand->SetPosition({ -450.f, -350.f });
	yggdrasilRightHand->Awake();
	yggdrasilRightHand->GetCollider()->SetScale({ 200.f,200.f });
	yggdrasilRightHand->GetRigidbody()->SetActive(false);

	yggdrasilEnergyBallBig = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new YggdrasilEnergyBallBig("YggdrasilEnergyBallBig"), LayerType::Boss);
	yggdrasilEnergyBallBig->SetYggdrasil(this);
	yggdrasilEnergyBallBig->SetPosition(yggdrasilHead->GetPosition());
	yggdrasilEnergyBallBig->Awake();
	yggdrasilEnergyBallBig->GetCollider()->SetScale({ 150.f,150.f });
	yggdrasilEnergyBallBig->GetRigidbody()->SetActive(false);

	attackTime = 0;
	attackDelay = 3.f;

	player = static_cast<Player*>(SceneManager::GetInstance().GetCurrentScene()->FindGameObject("Player", LayerType::Player));

	fsm.Start();
}

void Yggdrasil::Update(const float& deltaTime)
{
	//if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::Numpad7))
	//{
	//	fsm.ChangeState(YggdrasilStateType::FistAttack);
	//}
	//if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::Numpad8))
	//{
	//	fsm.ChangeState(YggdrasilStateType::SweepAttack);
	//}
	if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::Numpad9))
	{
		fsm.ChangeState(YggdrasilStateType::EnergyBallAttack);
	}
	fsm.Update(deltaTime);
}

void Yggdrasil::FixedUpdate(const float& deltaTime)
{
}

void Yggdrasil::LateUpdate(const float& deltaTime)
{
	fsm.LateUpdate(deltaTime);
}

sf::Vector2f Yggdrasil::GetHeadPos()
{
	return sf::Vector2f(yggdrasilHead->GetPosition());
}

sf::Vector2f Yggdrasil::GetLeftFistPos()
{
	return sf::Vector2f(yggdrasilLeftHand->GetPosition());
}

sf::Vector2f Yggdrasil::GetRightFistPos()
{
	return sf::Vector2f(yggdrasilRightHand->GetPosition());
}

void Yggdrasil::TakeDamage(float damage)
{
	currentStatus.hp -= damage;

	if (currentStatus.hp <= 0)
		OnDead();
}

void Yggdrasil::OnDead()
{
	 //fsm.ChangeState(YggdrasilStateType::Dead);
}

void Yggdrasil::SetLeftFistPos(sf::Vector2f pos)
{
	yggdrasilLeftHand->SetPosition(pos);
}

void Yggdrasil::SetRightFistPos(sf::Vector2f pos)
{
	yggdrasilRightHand->SetPosition(pos);
}

void Yggdrasil::OnCollisionEnter(Collider* target)
{
}

void Yggdrasil::OnCollisionStay(Collider* target)
{
}

void Yggdrasil::OnCollisionEnd(Collider* target)
{
}

PlayerSaveData Yggdrasil::GetPlayerSaveData() const
{
	return PlayerSaveData();
}

void Yggdrasil::LoadData(const PlayerSaveData& data)
{
}

Yggdrasil::Yggdrasil(const std::string& name)
	: AnimationGameObject(name)
	, fsm(this)
{
	rigidBody = new Rigidbody(this);
	rigidBody->SetGround(false);
	CreateCollider(ColliderType::Rectangle, ColliderLayer::Boss);
}

Yggdrasil::~Yggdrasil()
{
}
