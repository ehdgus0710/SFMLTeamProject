#include "stdafx.h"
#include "PlayerUIHub.h"
#include "Player.h"
#include "Scene.h"

#include "UITextGameObject.h"
#include "HpBarUI.h"

PlayerUIHub::PlayerUIHub(const std::string& texId, const std::string& name)
	: UISpriteGameObject(texId, name)
	, player(nullptr)
	, playerSmbolUI(nullptr)
	, hpText(nullptr)
	, maxHPText(nullptr)
	, playerHpBar(nullptr)


{
}

void PlayerUIHub::Awake()
{
	UISpriteGameObject::Awake();
}

void PlayerUIHub::SetPosition(const sf::Vector2f& pos)
{
	UISpriteGameObject::SetPosition(pos);
}

void PlayerUIHub::Render(sf::RenderWindow& renderWindow)
{
	UISpriteGameObject::Render(renderWindow);
}

void PlayerUIHub::Start()
{
	UISpriteGameObject::Start();

	player = static_cast<Player*>(SceneManager::GetInstance().GetCurrentScene()->FindGameObject("Player", LayerType::Player));
	Scene* scene = SceneManager::GetInstance().GetCurrentScene();

	playerSmbolUI = scene->AddGameObject(new UISpriteGameObject("SkulSimbul"), LayerType::UI);
	playerSmbolUI->SetPosition({ 100.f, 925.f });
	playerSmbolUI->SetScale({ 2.5f,2.5f });

	hpText = scene->AddGameObject(new UITextGameObject("DungGeunMo", "hpText", 30), LayerType::UI);
	maxHPText = scene->AddGameObject(new UITextGameObject("DungGeunMo", "maxHpText", 30), LayerType::UI);

	maxHPText->SetString(std::to_string((int)player->GetCurrentHP()));
	hpText->SetString(std::to_string((int)player->GetCurrentHP()));

	hpText->SetPosition({ 300.f, 1005.f });
	maxHPText->SetPosition({ 450.f, 1005.f });

	playerHpBar = scene->AddGameObject(new HpBarUI("", sf::Color::Red, "PlayerHPBar"), LayerType::UI);
	playerHpBar->SetOrigin(Origins::MiddleLeft);
	playerHpBar->SetPosition({ 160.f, 1015.f });
	playerHpBar->SetScale({ 400.f,30.f });
	playerHpBar->sortingOrder = 10;
	hpText->sortingOrder = 9;
	maxHPText->sortingOrder = 9;

}

void PlayerUIHub::Update(const float& deltaTime)
{
}

void PlayerUIHub::FixedUpdate(const float& deltaTime)
{
}

void PlayerUIHub::LateUpdate(const float& deltaTime)
{
}