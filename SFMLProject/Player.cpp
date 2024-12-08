#include "stdafx.h"
#include "Player.h"

#include "Rigidbody.h"
#include "Animator.h"
#include "Collider.h"
#include "Animation.h"

#include "GameManager.h"
#include "Camera.h"
#include "InGameScoreUI.h"
#include "Head.h"
#include "PlayerBaseState.h"
#include "PlayerHitState.h"
#include "PlayerUIHub.h"

Player::Player(const std::string& name)
	: AnimationGameObject(name)
	, fsm(this)
	, isJump(false)
	, currentStatus(150.f, 500.f, 200.f, 350.f)
	, reloadTime(0.2f)
	, currentReloadTime(0.f)
	, isReload(false)
	, isAttack(false)
	, isDead(false)
	, jumpCount(2)
	, currentJumpCount(2)
	, dashCount(2)
	, currentDashCount(2)
	, isNoneHead(false)
	, currentSkill1CoolTime(0.f)
	, currentSkill2CoolTime(0.f)
	, skill1CoolTime(2.f)
	, skill2CoolTime(3.f)
	, isSkll1CoolTime(false)
	, isSkll2CoolTime(false)
	, skullType(SkullType::Littlebone)
	
{	
	rigidBody = new Rigidbody(this);
	rigidBody->SetGround(false);
	CreateCollider(ColliderType::Rectangle, ColliderLayer::Player);

	animator->LoadCsv("animators/littlebone.csv");
	animator->LoadCsv("animators/noheadlittlebone.csv");

	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("SkullGet", "AudioClip/Skul/183_Skull_Get_a_v1.wav");
	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("SkullAttackHit1", "AudioClip/Skul/Skul_Hit 1.wav");
	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("SkullAttackHit2", "AudioClip/Skul/Skul_Hit 2.wav");
	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("SkullAttackHit3", "AudioClip/Skul/Skul_Hit 3.wav");
}

Player::~Player()
{
}

void Player::TakeDamage(const DamegeInfo& damage)
{
	if (fsm.GetCurrentStateType() == PlayerStateType::Dash)
		return;

	currentStatus.hp -= damage.damege;

	if (currentStatus.hp <= 0.f)
	{
		currentStatus.hp = 0.f;
		isDead = true;
		fsm.ChangeState(PlayerStateType::Dead);
	}
	else
	{
		if (damage.useKnockback && fsm.GetCurrentStateType() != PlayerStateType::Hit && fsm.GetCurrentStateType() != PlayerStateType::Dead)
		{
			static_cast<PlayerHitState*>(fsm.GetState(PlayerStateType::Hit))->SetDamageInfo(damage);
			fsm.ChangeState(PlayerStateType::Hit);
		}
	}

	if (changeHpAction != nullptr)
		changeHpAction(currentStatus.hp, currentStatus.maxHp);
}

void Player::OnDownJump()
{
	auto& targets = collider->GetCollisionTargets();
	bool isGround = false;
	for (auto& targetCollsion : targets)
	{
		if (targetCollsion->GetColliderLayer() == ColliderLayer::Wall)
		{
			Rectangle rect(collider->GetPosition(), collider->GetScale());
			Rectangle targetRect(targetCollsion->GetPosition(), targetCollsion->GetScale());

			if (rect.bottomPosition == targetRect.topPosition)
			{
				isGround = true;
				isJump = false;
				break;
			}
		}

	}

	if (!isGround)
	{
		rigidBody->SetGround(false);
		fsm.ChangeState(PlayerStateType::Falling);
	}
}

void Player::OnThrowHead()
{
	head->ThrowHead();
	head->SetActive(true);
	isNoneHead = true;
}

void Player::OnGetHead()
{
	SoundManger::GetInstance().PlaySfx("SkullGet");
	head->SetActive(false);
	isNoneHead = false;
	fsm.GetCurrentState()->SetChangeAnimationKey(0);
}

void Player::OnAttackHitSound(GameObject* object)
{
	int random = Utils::RandomRange(0, 2);

	if(random == 0)
		SoundManger::GetInstance().PlaySfx("SkullAttackHit1");
	else if (random == 1)
		SoundManger::GetInstance().PlaySfx("SkullAttackHit2");
	else
		SoundManger::GetInstance().PlaySfx("SkullAttackHit3");
}

void Player::OnSkill1CoolTime()
{
	isSkll1CoolTime = true;
	currentSkill1CoolTime = 0.f;

	playerUI->OnSkill1CoolTime();
}

void Player::OnSkill2CoolTime()
{
	isSkll2CoolTime = true;
	currentSkill2CoolTime = 0.f;

	playerUI->OnSkill2CoolTime();
}


void Player::SetHeadPosition(sf::Vector2f pos)
{
	head->SetPosition(pos);
}

sf::Vector2f Player::GetHeadPosition()
{
	return head->GetPosition();
}
void Player::AddHp(float hp)
{
	currentStatus.hp += hp;

	if (currentStatus.hp > currentStatus.maxHp)
		currentStatus.hp = currentStatus.maxHp;

	if (changeHpAction)
		changeHpAction(currentStatus.hp, currentStatus.maxHp);
}
void Player::SetMaxHp(float maxHp)
{
	currentStatus.maxHp = maxHp;

	if (changeHpAction)
		changeHpAction(currentStatus.hp, currentStatus.maxHp);
}
void Player::Awake()
{
	AnimationGameObject::Awake();
	currentDashCount = dashCount;
	currentJumpCount = jumpCount;
	dashDelayTime = 1.3f;

	// Player UI
	TEXTURE_MANAGER.Load("PlayerUiFrame", "graphics/UI/PlayerUI/player_ui_frame.png");
	TEXTURE_MANAGER.Load("SkulSimbul", "graphics/UI/PlayerUI/Skul.png");
	TEXTURE_MANAGER.Load("SkullThrow", "graphics/UI/PlayerUI/skull_throw.png");
	TEXTURE_MANAGER.Load("Rebone", "graphics/UI/PlayerUI/rebone.png");
	TEXTURE_MANAGER.Load("PlayerHealthBar", "graphics/UI/PlayerUI/Player_HealthBar.png");

	// Player Font
	ResourcesManager<sf::Font>::GetInstance().Load("Status", "fonts/Perfect DOS VGA 437.ttf", true);
	ResourcesManager<sf::Font>::GetInstance().Load("NameFont2", "fonts/NotoSans-Bold.ttf", true);
	ResourcesManager<sf::Font>::GetInstance().Load("NameFont", "fonts/D2Coding.ttc", true);
}

void Player::Start()
{
	AnimationGameObject::Start();
	fsm.Start();
	animator->ChangeAnimation("noheadlittleboneIdle", true);

	SetScale({ 3.f,3.f });
	collider->SetScale({ 16.f,32.f });
	collider->SetOffsetPosition({ 0.f, -5.f });

	head = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new Head("Head"), LayerType::PlayerBullet);
	head->SetPlayer(this);
	head->Awake();
	head->SetActive(false);

	playerUI = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new PlayerUIHub("PlayerUiFrame"), LayerType::InGameUI);

	playerUI->SetOrigin(Origins::BottomLeft);
	playerUI->SetScale({ 3.5f,3.5f });
	playerUI->SetPosition({ 0, 1075.f });
}

void Player::Update(const float& deltaTime)
{
	fsm.Update(deltaTime);
	animator->Update(deltaTime);
	if (currentDashCount <= 0)
	{
		currentDashDelayTime += deltaTime;
		if (currentDashDelayTime > dashDelayTime)
		{
			currentDashCount = dashCount;
			currentDashDelayTime = 0.f;
		}
	}

	if (isSkll1CoolTime)
	{
		currentSkill1CoolTime += deltaTime;

		if(skill1CooltimeAction)
			skill1CooltimeAction(currentSkill1CoolTime, skill1CoolTime);

		if (currentSkill1CoolTime >= skill1CoolTime)
		{
			isSkll1CoolTime = false;
			OnGetHead();
		}
	}

	if (isSkll2CoolTime)
	{
		currentSkill2CoolTime += deltaTime;
		
		if (skill2CooltimeAction)
			skill2CooltimeAction(currentSkill2CoolTime, skill2CoolTime);

		if (currentSkill2CoolTime >= skill2CoolTime)
			isSkll2CoolTime = false;
	}

	if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::A))
	{
		if(!isSkll1CoolTime && fsm.GetCurrentStateType() != PlayerStateType::Skill1 && fsm.GetCurrentStateType() != PlayerStateType::Dead)
			fsm.ChangeState(PlayerStateType::Skill1);
	}

	if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::S) && head->IsActive())
	{
		if (!isSkll2CoolTime && fsm.GetCurrentStateType() != PlayerStateType::Skill2 && fsm.GetCurrentStateType() != PlayerStateType::Dead)
			fsm.ChangeState(PlayerStateType::Skill2);
	}

	if (fsm.GetCurrentStateType() != PlayerStateType::Falling && fsm.GetCurrentStateType() != PlayerStateType::Hit && fsm.GetCurrentStateType() != PlayerStateType::JumpAttack && rigidBody->GetActive() && rigidBody->GetCurrentVelocity().y > 0.f)
		fsm.ChangeState(PlayerStateType::Falling);

	/*if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::Numpad7))
	{
		DamegeInfo damageInfo;
		damageInfo.damege = 10.f;
		damageInfo.useKnockback = true;
		damageInfo.knockbackDuration = 0.4f;
		damageInfo.owner = this;
		damageInfo.knockbackVelocity = { 50.f,0.f };
		damageInfo.hitDirection = sf::Vector2f::down;
		TakeDamage(damageInfo);
	}
	else if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::Numpad8))
	{
		DamegeInfo damageInfo;
		damageInfo.damege = 10.f;
		damageInfo.useKnockback = true;
		damageInfo.knockbackDuration = 0.4f;
		damageInfo.owner = this;
		damageInfo.knockbackVelocity = { 800.f,- 600.f };
		damageInfo.hitDirection = sf::Vector2f::Normalized(damageInfo.knockbackVelocity);
		TakeDamage(damageInfo);
	}*/
}

void Player::FixedUpdate(const float& deltaTime)
{
	fsm.FixedUpdate(deltaTime);
	rigidBody->FixedUpdate(deltaTime);
}

void Player::LateUpdate(const float& deltaTime)
{
	fsm.LateUpdate(deltaTime);
}

void Player::Render(sf::RenderWindow& renderWindow)
{
	if(!isDead)
		AnimationGameObject::Render(renderWindow);
}

void Player::OnCollisionEnter(Collider* target)
{
	if (target->GetOwner() == head && !head->IsOnSkill())
		OnGetHead();
}
void Player::OnCollisionStay(Collider* target)
{
}
void Player::OnCollisionEnd(Collider* target)
{
	if (target->GetColliderLayer() == ColliderLayer::Wall || target->GetColliderLayer() == ColliderLayer::Scaffolding)
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
				isJump = false;
				break;
			}
		}

		if (!isGround)
		{
			rigidBody->SetGround(false);
			currentJumpCount = 1;
		}
		else
		{
			currentJumpCount = jumpCount;
		}
	}
}

PlayerSaveData Player::GetPlayerSaveData() const
{
	return PlayerSaveData({ this->GetGameObjectSaveData(), currentStatus });
}

void Player::LoadData(const PlayerSaveData& data)
{
	LoadGameObjectData(data.gameObjectSaveData);
	currentStatus = data.status;
}
