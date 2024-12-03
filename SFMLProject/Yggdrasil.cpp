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
#include "yggdrasilMouth.h"
#include "YggdrasilHead.h"
#include "YggdrasilLeftHand.h"
#include "YggdrasilRightHand.h"
#include "YggdrasilEnergyBallBig.h"
#include "YggdrasilEnergyBallSmall.h"
#include "Player.h"


Yggdrasil::Yggdrasil(const std::string& name)
	: AnimationGameObject(name)
	, fsm(this)
{
	rigidBody = new Rigidbody(this);
	rigidBody->SetGround(false);
	CreateCollider(ColliderType::Rectangle, ColliderLayer::Boss);
	SetScale({ 4.f, 4.f });

	animator->LoadCsv("animators/yggdrasilBody.csv");
}

Yggdrasil::~Yggdrasil()
{
}

void Yggdrasil::Awake()
{
	AnimationGameObject::Awake();
}

void Yggdrasil::Start()
{
	AnimationGameObject::Start();

	animator->ChangeAnimation("phase1Head", true);


	InputManager::GetInstance().BindKey(sf::Keyboard::Numpad7);
	InputManager::GetInstance().BindKey(sf::Keyboard::Numpad8);
	InputManager::GetInstance().BindKey(sf::Keyboard::Numpad9);

	yggdrasilHead = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new YggdrasilHead("YggdrasilHead"), LayerType::Boss);
	yggdrasilHead->SetYggdrasil(this);
	yggdrasilHead->SetPosition({ GetPosition().x, GetPosition().y - 150.f });
	yggdrasilHead->Awake();
	yggdrasilHead->GetCollider()->SetScale({ 200.f,200.f });
	yggdrasilHead->GetRigidbody()->SetActive(false);

	yggdrasilMouth = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new YggdrasilMouth("yggdrasilMouth"), LayerType::Boss);
	yggdrasilMouth->SetYggdrasil(this);
	yggdrasilMouth->SetPosition({ yggdrasilHead->GetPosition().x + 50.f, yggdrasilHead->GetPosition().y + 300.f });
	yggdrasilMouth->Awake();
	yggdrasilMouth->GetCollider()->SetScale({ 200.f,200.f });
	yggdrasilMouth->GetRigidbody()->SetActive(false);

	yggdrasilLeftHand = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new YggdrasilLeftHand("yggdrasilLeftHand"), LayerType::Boss);
	yggdrasilLeftHand->SetYggdrasil(this);
	yggdrasilLeftHand->SetPosition({ GetPosition().x + 700.f, GetPosition().y + 300.f });
	yggdrasilLeftHand->Awake();
	yggdrasilLeftHand->GetCollider()->SetScale({ 200.f,200.f });
	yggdrasilLeftHand->GetRigidbody()->SetActive(false);

	yggdrasilRightHand = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new YggdrasilRightHand("YggdrasilRightHand"), LayerType::Boss);
	yggdrasilRightHand->SetYggdrasil(this);
	yggdrasilRightHand->SetPosition({ GetPosition().x - 700.f, GetPosition().y + 300.f });
	yggdrasilRightHand->Awake();
	yggdrasilRightHand->GetCollider()->SetScale({ 200.f,200.f });
	yggdrasilRightHand->GetRigidbody()->SetActive(false);

	attackTime = 0;
	attackDelay = 3.f;

	player = static_cast<Player*>(SceneManager::GetInstance().GetCurrentScene()->FindGameObject("Player", LayerType::Player));

	fsm.Start();
}

void Yggdrasil::Update(const float& deltaTime)
{
	animator->Update(deltaTime);
	//if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::Numpad7))
	//{
	//	fsm.ChangeState(YggdrasilStateType::FistAttack);
	//}
	//if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::Numpad8))
	//{
	//	fsm.ChangeState(YggdrasilStateType::SweepAttack);
	//}
	//if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::Numpad9))
	//{
	//	fsm.ChangeState(YggdrasilStateType::EnergyBallAttack);
	//}
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

void Yggdrasil::TakeDamage(const DamegeInfo& damage)
{
	/*currentStatus.hp -= damage.damege;

	if (currentStatus.hp <= 0)
		OnDead();*/
}

void Yggdrasil::OnDead()
{
	//fsm.ChangeState(YggdrasilStateType::Dead);
}

void Yggdrasil::SetAnimeLeftHand(std::string name, bool loop)
{
	yggdrasilLeftHand->SetAniLeftHand(name, loop);
}

void Yggdrasil::SetAnimeRightHand(std::string name, bool loop)
{
	yggdrasilRightHand->SetAniRightHand(name, loop);
}
void Yggdrasil::SetHeadPos(sf::Vector2f pos)
{
	yggdrasilHead->SetPosition(pos);
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

