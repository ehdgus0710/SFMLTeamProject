#include "stdafx.h"
#include "Player.h"

#include "Rigidbody.h"
#include "Animator.h"
#include "Collider.h"
#include "Animation.h"
#include "FireBullet.h"

#include "GameManager.h"
#include "Camera.h"
#include "InGameScoreUI.h"

Player::Player(const std::string& name)
	: GameObject(name)
	, fsm(this)
	, isJump(false)
	, currentStatus(2, 500.f, 200.f, 350.f)
	, isFlipX(false)
	, hitTime(2.f)
	, currentHitTime(0.f)
	, reloadTime(0.2f)
	, currentReloadTime(0.f)
	, isReload(false)
	, isAttack(false)
	, currentStarState(0.f)
	, starStateTime(9.f)
	, isStarState(false)
	, colorChangeTime(0.1f)
	, currentColorTime(0.f)
	, currentColorIndex(0)
	, isDead(false)
{
	rigidBody = new Rigidbody(this);
	rigidBody->SetGround(false);
	CreateAnimator();
	animator->LoadCsv("animators/mario.csv");
	CreateCollider(ColliderType::Rectangle, ColliderLayer::Player);

	defaultColor = sprite.getColor();
	effectColor = defaultColor;
	effectColor.a = 120;

	animator->GetAnimation("marioFireIdleAttack")->SetAnimationEndEvent(std::bind(&Player::OnAttackEnd, this), 0);
	animator->GetAnimation("marioFireRunAttack")->SetAnimationEndEvent(std::bind(&Player::OnAttackEnd, this), 1);
	animator->GetAnimation("marioFireJumpAttack")->SetAnimationEndEvent(std::bind(&Player::OnAttackEnd, this), 0);

	starStateChangeColors[0] = { 230,230,230,255 };
	starStateChangeColors[1] = { 230,200,20,255 };
	starStateChangeColors[2] = { 58,132,0,255 };
	starStateChangeColors[3] = { 230,156,33,255 };
}

Player::~Player()
{
}

void Player::ChangeSmallMario()
{
	currentStatus.hp = 1;
	collider->SetScale({32.f, 64.f});
	fsm.ChangeState(PlayerStateType::Idle);
}

void Player::ChangeMario(int hp)
{
	currentStatus.hp = hp;
	if (hp == 1)
		ChangeSmallMario();
	else
	{
		collider->SetScale({ 64.f, 128.f });
		fsm.ChangeState(PlayerStateType::Idle);
	}
}

void Player::OnStarState()
{
	isStarState = true;
	currentStarState = 0.f;
	SoundManger::GetInstance().PlayBgm("Invincible");
}

void Player::Awake()
{
}

void Player::Start()
{
	SetScale(scale);
	SetPosition(position);
	SetRotation(rotation);

	SetOrigin(originPreset);
	animator->Start();
	collider->Reset();

	fsm.Start();
	fsm.ChangeState(PlayerStateType::Idle);

	if(currentStatus.hp == 1)
		GetCollider()->SetScale({ 32.f, 64});
	else
		GetCollider()->SetScale({ (sf::Vector2f)animator->GetCurrentAnimation()->GetFrameInfo()[0].rectSize });

	mainCamera = SceneManager::GetInstance().GetCurrentScene()->GetMainCamera();

}

void Player::TakeDamage()
{
	if (isHit)
		return;

	--currentStatus.hp;
	isHit = true;

	if (currentStatus.hp == 0)
	{
		isDead = true;
		fsm.ChangeState(PlayerStateType::Dead);
		return;
	}
	else
	{ 
		fsm.ChangeState(PlayerStateType::Hit);
		sprite.setColor(effectColor);
	}

	currentHitTime = hitTime;
}

void Player::OnFlipX()
{
	isFlipX = !isFlipX;

	scale.x *= -1.f;
	SetScale(scale);
}

void Player::AddItem(ItemType itemType)
{
	switch (itemType)
	{
	case ItemType::Coin:
		GameManager::GetInstance().HaveCoin();
		break;
	case ItemType::MushRoom:
		if (currentStatus.hp == 1)
		{
			fsm.ChangeState(PlayerStateType::Upgrade);
		}
		else if (currentStatus.hp > 1)
		{
			GameManager::GetInstance().OnLifeUp();

			InGameScoreUI* inGameScoreUI = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new InGameScoreUI("DungGeunMo", "MushRoomScore", 30), LayerType::InGameUI);
			inGameScoreUI->SetString("1UP");
			inGameScoreUI->SetPosition(position + sf::Vector2f::up * 20.f);
			inGameScoreUI->Start();
			SoundManger::GetInstance().PlaySfx("OneUp");
		}
		break;
	case ItemType::Flower:
		if(currentStatus.hp < 3)
			fsm.ChangeState(PlayerStateType::Upgrade);
		break;
	case ItemType::Star:
	{
		OnStarState();
	}
		break;
	case ItemType::End:
		break;
	default:
		break;
	}
}
void Player::TakeUpgrade()
{
	// fsm.ChangeState(PlayerStateType::Upgrade);
}

void Player::Attack()
{
	if ( isAttack || isReload || isStarState || currentStatus.hp < 3)
		return;

	if (!(fsm.GetCurrentStateType() == PlayerStateType::Idle || fsm.GetCurrentStateType() == PlayerStateType::Jump || fsm.GetCurrentStateType() == PlayerStateType::Run))
		return;

	FireBullet* bullet = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new FireBullet(), LayerType::PlayerBullet);

	sf::Vector2f direciton;
	
	if (isFlipX)
	{
		direciton = sf::Vector2f::left;
		bullet->SetPosition(position + sf::Vector2f::left * 32.f);
	}
	else
	{
		direciton = sf::Vector2f::right;
		bullet->SetPosition(position + sf::Vector2f::right * 32.f);
	}

	direciton.Normalized();

	bullet->SetMoveDirection(direciton);
	bullet->GetRigidbody()->SetVelocity({ 0.f, 0.f });
	
	bullet->Awake();
	bullet->Start();

	if (fsm.GetCurrentStateType() == PlayerStateType::Idle)
	{
		animator->ChangeAnimation("marioFireIdleAttack");
	}
	else if (fsm.GetCurrentStateType() == PlayerStateType::Jump)
	{
		animator->ChangeAnimation("marioFireJumpAttack");
	}
	else if (fsm.GetCurrentStateType() == PlayerStateType::Run)
	{
		animator->ChangeAnimation("marioFireRunAttack");
	}

	SoundManger::GetInstance().PlaySfx("Fireball");
}

void Player::OnAttackEnd()
{
	isAttack = false;
	isReload = true;

	if (fsm.GetCurrentStateType() == PlayerStateType::Idle)
	{
		animator->ChangeAnimation("marioFireIdle", true);
	}
	else if (fsm.GetCurrentStateType() == PlayerStateType::Jump)
	{
		animator->ChangeAnimation("marioFireJump", true);
	}
	else if (fsm.GetCurrentStateType() == PlayerStateType::Run)
	{
		animator->ChangeAnimation("marioFireRun", true);
	}
}


void Player::Update(const float& deltaTime)
{
	fsm.Update(deltaTime);
	animator->Update(deltaTime);

	if (isHit)
	{
		currentHitTime -= deltaTime;
 
		if (currentHitTime <= 0.f)
		{
			sprite.setColor(defaultColor);
			isHit = false;
			currentHitTime = 0.f;
		}
	}

	if (InputManager::GetInstance().GetKeyPressed(sf::Keyboard::LShift))
	{
		isRun = true;
		animator->SetAnimationSpeed(2.f);
	}
	else
	{
		isRun = false;
		animator->SetAnimationSpeed(1.f);
	}


	if (!isDead && position.y >= 3000.f)
	{
		fsm.ChangeState(PlayerStateType::Dead);
		isDead = true;
	}

	if (position.x - abs(collider->GetScale().x * 0.5f) < mainCamera->GetCameraLeftPosition())
	{
		position.x = mainCamera->GetCameraLeftPosition() + abs(collider->GetScale().x * 0.5f);
		SetPosition(position);
	}
	if (isStarState)
	{
		currentStarState += deltaTime;
		currentColorTime += deltaTime;

		if (currentColorTime >= colorChangeTime)
		{
			sprite.setColor(starStateChangeColors[currentColorIndex]);
			currentColorTime = 0.f;

			currentColorIndex = currentColorIndex == 3 ? 0 : currentColorIndex + 1;
		}

		if (currentStarState >= starStateTime)
		{
			currentStarState = 0.f;
			isStarState = false;
			sprite.setColor(defaultColor);
			SoundManger::GetInstance().PlayBgm("MainTheme");
		}
	}

	if (isReload)
	{
		currentReloadTime += deltaTime;
		if (currentReloadTime >= reloadTime)
		{
			currentReloadTime = 0.f;
			isReload = false;
		}
	}
}

void Player::FixedUpdate(const float& deltaTime)
{
	fsm.FixedUpdate(deltaTime);
	rigidBody->FixedUpdate(deltaTime); 

	/*if (!isHit)
	{
		if (position.y >= 0.f)
		{
			isJump = false;
			position.y = 0.f;

			rigidBody->SetGround(true);
			SetPosition(position);
		}
	}*/
	
}

void Player::LateUpdate(const float& deltaTime)
{
	fsm.LateUpdate(deltaTime);
}

void Player::Render(sf::RenderWindow& renderWindow)
{
	animator->Render(renderWindow);
	collider->Render(renderWindow);
}
void Player::OnCollisionEnter(Collider* target)
{
}
void Player::OnCollisionStay(Collider* target)
{
}
void Player::OnCollisionEnd(Collider* target)
{
	if (target->GetColliderLayer() == ColliderLayer::Wall || target->GetColliderLayer() == ColliderLayer::Block)
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
			if(!isJump)
				rigidBody->AddDropSpeed(30.f);

			rigidBody->SetGround(false);
		}
	}
	
}
void Player::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	sprite.setPosition(pos);
	collider->SetPosition(pos);
}

void Player::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;

	animator->SetScale(scale);
	collider->SetOwnerScale(scale);
}

void Player::SetRotation(float angle)
{
	rotation = angle;
	sprite.rotate(angle);
	collider->SetRotation(angle);
}

void Player::SetOrigin(Origins preset)
{
	originPreset = preset;
	origin = Utils::SetOrigin(sprite, preset);
	collider->SetOrigin(preset);
}

void Player::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	sprite.setOrigin(origin);	
	collider->SetOrigin(newOrigin);
}

void Player::CreateAnimator()
{
	if (animator != nullptr)
		return;

	animator = new Animator(this, sprite);
}

sf::FloatRect Player::GetLocalBounds() const
{
	return sprite.getLocalBounds();
}

sf::FloatRect Player::GetGlobalBounds() const
{
	return sprite.getGlobalBounds();
}

PlayerSaveData Player::GetPlayerSaveData() const
{
	return PlayerSaveData({this->GetGameObjectSaveData(), currentStatus});
}

void Player::LoadData(const PlayerSaveData& data)
{
	LoadGameObjectData(data.gameObjectSaveData);
	currentStatus = data.status;
}
