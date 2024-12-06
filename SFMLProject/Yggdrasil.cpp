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
#include "YggdrasilUIHub.h"
#include "Player.h"


Yggdrasil::Yggdrasil(const std::string& name)
	: AnimationGameObject(name)
	, fsm(this)
{
	rigidBody = new Rigidbody(this);
	rigidBody->SetGround(false);
	rigidBody->Disable();
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

	// Yggdrasil UI
	TEXTURE_MANAGER.Load("BossHealthBarFirstPhase", "graphics/UI/BossUI/BossHealthBar_FirstPhase.png");
	TEXTURE_MANAGER.Load("BossHealthBarSecondPhase", "graphics/UI/BossUI/BossHealthBar_SecondPhase.png");
	TEXTURE_MANAGER.Load("YggdrasilFirstPhaseBottomBack", "graphics/boss/Yggdrasil/UI/Ch1BossFirstPhase_BottomBack.png");
	TEXTURE_MANAGER.Load("YggdrasilFirstPhaseFront", "graphics/boss/Yggdrasil/UI/Ch1BossFirstPhase_Front.png");
	TEXTURE_MANAGER.Load("YggdrasilFirstPhaseTopBack", "graphics/boss/Yggdrasil/UI/Ch1BossFirstPhase_Top_Back.png");
	TEXTURE_MANAGER.Load("YggdrasilSecondPhaseBottomBack", "graphics/boss/Yggdrasil/UI/Ch1BossSecondPhase_Bottom_Back.png");
	TEXTURE_MANAGER.Load("YggdrasilSecondPhaseFront", "graphics/boss/Yggdrasil/UI/Ch1BossSecondPhase_Front.png");
	TEXTURE_MANAGER.Load("YggdrasilSecondPhaseTop", "graphics/boss/Yggdrasil/UI/Ch1BossSecondPhase_Top_Back.png");
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
	yggdrasilHead->GetCollider()->SetScale({ 150.f,150.f });
	yggdrasilHead->GetRigidbody()->SetActive(false);

	yggdrasilMouth = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new YggdrasilMouth("yggdrasilMouth"), LayerType::Boss);
	yggdrasilMouth->SetYggdrasil(this);
	yggdrasilMouth->SetPosition({ GetPosition().x + 50, GetPosition().y + 150.f });
	yggdrasilMouth->Awake();
	yggdrasilMouth->GetCollider()->SetScale({ 100.f,100.f });
	yggdrasilMouth->GetRigidbody()->SetActive(false);

	yggdrasilLeftHand = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new YggdrasilLeftHand("yggdrasilLeftHand"), LayerType::Boss);
	yggdrasilLeftHand->SetYggdrasil(this);
	yggdrasilLeftHand->SetPosition({ GetPosition().x + 700.f, GetPosition().y + 250.f });
	yggdrasilLeftHand->Awake();
	yggdrasilLeftHand->GetCollider()->SetScale({ 150.f,150.f });
	yggdrasilLeftHand->GetRigidbody()->SetActive(false);

	yggdrasilRightHand = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new YggdrasilRightHand("YggdrasilRightHand"), LayerType::Boss);
	yggdrasilRightHand->SetYggdrasil(this);
	yggdrasilRightHand->SetPosition({ GetPosition().x - 700.f, GetPosition().y + 250.f });
	yggdrasilRightHand->Awake();
	yggdrasilRightHand->GetCollider()->SetScale({ 150.f,150.f });
	yggdrasilRightHand->GetRigidbody()->SetActive(false);

	yggdrasilUIHub = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new YggdrasilUIHub("YggdrasilUIHub"), LayerType::InGameUI);
	yggdrasilUIHub->SetOrigin(Origins::BottomLeft);
	yggdrasilUIHub->SetScale({ 3.5f,3.5f });
	yggdrasilUIHub->SetPosition({ 0, 1075.f });

	attackTime = 0;
	attackDelay = 3.f;

	phase1Hp = 1000;
	phase2Hp = 1000;

	phaseUp = false;


	player = static_cast<Player*>(SceneManager::GetInstance().GetCurrentScene()->FindGameObject("Player", LayerType::Player));

	fsm.Start();
}

void Yggdrasil::Update(const float& deltaTime)
{
	animator->Update(deltaTime);
	/*if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::A))
	{
		phaseUp = true;
	}*/
	if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::Numpad7))
	{
		fsm.ChangeState(YggdrasilStateType::Dead);
	}
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

sf::Vector2f Yggdrasil::GetMouthPos()
{
	return sf::Vector2f(yggdrasilMouth->GetPosition());
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
	if (fsm.GetCurrentStateType() == YggdrasilStateType::Dead)
		return;

	currentStatus.hp -= damage.damege;

	if (currentStatus.hp <= 0.f)
	{
		currentStatus.hp = 0.f;
		/*isDead = true;
		fsm.ChangeState(PlayerStateType::Dead);*/

		if (!phaseUp)
		{
			phaseUp = true;
			currentStatus.hp = (float)phase2Hp;
			currentStatus.maxHp = (float)phase2Hp;
		}
	}

	if (changeHpAction != nullptr)
		changeHpAction(currentStatus.hp, currentStatus.maxHp);
}

void Yggdrasil::OnDead()
{
	//fsm.ChangeState(YggdrasilStateType::Dead);
}

void Yggdrasil::SetAnimeBody(std::string name, bool loop)
{
	animator->ChangeAnimation(name, loop);
}

void Yggdrasil::SetAnimeHead(std::string name, bool loop)
{
	yggdrasilHead->SetAniHead(name, loop);
}

void Yggdrasil::SetAnimeMouth(std::string name, bool loop)
{
	yggdrasilMouth->SetAniMouth(name, loop);
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

void Yggdrasil::SetMouthPos(sf::Vector2f pos)
{
	yggdrasilMouth->SetPosition(pos);
}

void Yggdrasil::SetLeftFistPos(sf::Vector2f pos)
{
	yggdrasilLeftHand->SetPosition(pos);
}

void Yggdrasil::SetRightFistPos(sf::Vector2f pos)
{
	yggdrasilRightHand->SetPosition(pos);
}

void Yggdrasil::SetHeadRota(float rota)
{
	yggdrasilHead->SetRotation(rota);
}

void Yggdrasil::SetMouthRota(float rota)
{
	yggdrasilMouth->SetRotation(rota);
}

void Yggdrasil::SetLeftFistRota(float rota)
{
	yggdrasilLeftHand->SetRotation(rota);
}

void Yggdrasil::SetRightFistRota(float rota)
{
	yggdrasilRightHand->SetRotation(rota);
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

