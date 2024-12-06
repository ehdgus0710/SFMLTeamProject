#include "stdafx.h"
#include "YggdrasilUIHub.h"

#include "Scene.h"
#include "UITextGameObject.h"
#include "HpBarUI.h"
#include "Yggdrasil.h"

YggdrasilUIHub::YggdrasilUIHub(const std::string& texId, const std::string& name)
	: UISpriteGameObject(texId, name)
	, frontHpBarSprite(nullptr)
	, hpBar(nullptr)
	, nameText(nullptr)
	, tribeText(nullptr)
	, yggdrasil(nullptr)
	, topBackSprite(nullptr)
	, bottomBackSprite(nullptr)
{
}

void YggdrasilUIHub::ChangeHP(float currentHp, float maxHp)
{
	hpBar->ChangeHP(currentHp, maxHp);
}
void YggdrasilUIHub::ChangePhase()
{
	bottomBackSprite->ChangeSprite("YggdrasilSecondPhaseBottomBack");
	topBackSprite->ChangeSprite("YggdrasilSecondPhaseFront");
	frontHpBarSprite->ChangeSprite("YggdrasilSecondPhaseTop");

	hpBar->ChangeSprite("BossHealthBarSecondPhase");
	nameText->SetString(L"각성한 위그드라실");

	frontHpBarSprite->SetPosition({ 960.f, 70.f });
	topBackSprite->SetPosition({ 960.f, 85.f });
	bottomBackSprite->SetPosition({ 960.f,85.f });

	hpBar->SetPosition({ 549.f, 80.f });
	hpBar->SetMaxHpBarSize({ 823.f,30.f });

	nameText->SetPosition({ 960.f, 45.f });
	tribeText->SetPosition({ 960.f, 120.f });
}
void YggdrasilUIHub::SetPosition(const sf::Vector2f& pos)
{
	UISpriteGameObject::SetPosition(pos);
}

void YggdrasilUIHub::Start()
{
	UISpriteGameObject::Start();

	Scene* scene = SceneManager::GetInstance().GetCurrentScene();
	yggdrasil = static_cast<Yggdrasil*>(SceneManager::GetInstance().GetCurrentScene()->FindGameObject("Yggdrasil", LayerType::Boss));

	nameText = scene->AddGameObject(new UITextGameObject("NameFont", "yggdrasilNameText", 15), LayerType::UI);
	tribeText = scene->AddGameObject(new UITextGameObject("NameFont", "yggdrasilTribeText", 15), LayerType::UI);

	bottomBackSprite = scene->AddGameObject(new UISpriteGameObject("YggdrasilFirstPhaseBottomBack", "YggdrasilFirstPhaseBottomBack"), LayerType::UI);
	topBackSprite = scene->AddGameObject(new UISpriteGameObject("YggdrasilFirstPhaseTopBack", "YggdrasilFirstPhaseTopBack"), LayerType::UI);
	
	topBackSprite->SetScale({ 3.f, 3.f });
	topBackSprite->SetPosition({ 960.f,85.f});

	bottomBackSprite->SetScale({ 2.f, 2.5f });
	bottomBackSprite->SetPosition({ 960.f,85.f });

	nameText->SetString(L"위그드라실");
	tribeText->SetString(L"엘로 장로");
	nameText->SetPosition({ 960.f, 55.f });
	tribeText->SetPosition({ 960.f, 125.f });

	hpBar = scene->AddGameObject(new HpBarUI("BossHealthBarFirstPhase", "BossHealthBar"), LayerType::UI);
	hpBar->SetOrigin(Origins::MiddleLeft);
	hpBar->SetPosition({ 618.f, 98.f });
	hpBar->SetMaxHpBarSize({ 685.f,25.f });
	
	frontHpBarSprite = scene->AddGameObject(new UISpriteGameObject("YggdrasilFirstPhaseFront", "YggdrasilFront"), LayerType::UI);
	frontHpBarSprite->SetPosition({ 960.f, 85.f });
	frontHpBarSprite->SetScale({ 2.5f, 2.5f });

	bottomBackSprite->sortingOrder = 18;
	topBackSprite->sortingOrder = 18;
	frontHpBarSprite->sortingOrder = 16;
	hpBar->sortingOrder = 15;
	sortingOrder = 14;
	nameText->sortingOrder = 13;
	nameText->sortingOrder = 13;


	yggdrasil->SetChangeHpAction(std::bind(&YggdrasilUIHub::ChangeHP, this, std::placeholders::_1, std::placeholders::_2));
}
void YggdrasilUIHub::Update(const float& deltaTime)
{
	if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::A))
	{
		ChangePhase();
	}
}