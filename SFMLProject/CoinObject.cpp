#include "stdafx.h"
#include "CoinObject.h"
#include "Animator.h"
#include "Collider.h"
#include "Animation.h"
#include "Rigidbody.h"
#include "InGameScoreUI.h"
#include "Scene.h"

CoinObject::CoinObject()
	: ItemObject(ItemType::Coin, "Items", "Coin")
	, isGetCoin(false)
{
	CreateAnimator();

	animator->LoadCsv("animators/coin.csv");
}

void CoinObject::Start()
{
	SetScale(scale);
	SetPosition(position);
	SetRotation(rotation);

	SetOrigin(originPreset);
	animator->Start();
	collider->Reset();
	collider->SetScale({ (sf::Vector2f)animator->GetCurrentAnimation()->GetFrameInfo()[0].rectSize });
	animator->ChangeAnimation("coinIdle", true);
}

void CoinObject::Update(const float& deltaTime)
{
	animator->Update(deltaTime);

	if (isCreateEvent)
	{
		if (position.y >= createEndPosition.y)
			SetDestory(true);
	}
}

void CoinObject::FixedUpdate(const float& deltaTime)
{
	rigidBody->FixedUpdate(deltaTime);
}

void CoinObject::CreateAnimator()
{
	if (animator == nullptr)
		animator = new Animator(this, sprite);
}

void CoinObject::CreateEvenet()
{
	isCreateEvent = true;
	isGetCoin = true;
	collider->SetActive(false);
	createEndPosition = position;
	createEndPosition.y += 20.f;
	rigidBody = new Rigidbody(this);
	rigidBody->SetVelocity({ 0, -800.f });
	rigidBody->SetGround(false);
	
	SoundManger::GetInstance().PlaySfx("Coin");

	InGameScoreUI* inGameScoreUI = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new InGameScoreUI("DungGeunMo", "CoinScoreUI", 30), LayerType::InGameUI);
	inGameScoreUI->SetString("200");
	inGameScoreUI->SetPosition(position + sf::Vector2f::up * 30.f);
	inGameScoreUI->Start();
}
