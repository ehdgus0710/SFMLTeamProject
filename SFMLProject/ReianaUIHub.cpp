#include "stdafx.h"
#include "ReianaUIHub.h"
#include "UITextGameObject.h"
#include "HpBarUI.h"


ReianaUIHub::ReianaUIHub(const std::string& texId, const std::string& name)
	: UISpriteGameObject(texId, name)
	, topBackSprite(nullptr)
	, bottomBackSprite(nullptr)
	, frontHpBarSprite(nullptr)
	, reianaAHPBar(nullptr)
	, reianaBHPBar(nullptr)
	, nameText(nullptr)
	, tribeText(nullptr)

{
}

void ReianaUIHub::Start()
{
	UISpriteGameObject::Start();

	Scene* scene = SceneManager::GetInstance().GetCurrentScene();
	// yggdrasil = static_cast<Yggdrasil*>(SceneManager::GetInstance().GetCurrentScene()->FindGameObject("Yggdrasil", LayerType::Boss));

	nameText = scene->AddGameObject(new UITextGameObject("NameFont", "ReianaNameText", 15), LayerType::UI);
	tribeText = scene->AddGameObject(new UITextGameObject("NameFont", "ReianaTribeText", 15), LayerType::UI);

	bottomBackSprite = scene->AddGameObject(new UISpriteGameObject("Ch2BossFirstPhaseBottomBack", "Ch2BossFirstPhaseBottomBack"), LayerType::UI);
	topBackSprite = scene->AddGameObject(new UISpriteGameObject("Ch2BossFirstPhaseTopBack", "Ch2BossFirstPhaseTopBack"), LayerType::UI);

	frontHpBarSprite = scene->AddGameObject(new UISpriteGameObject("Ch2BossFirstPhaseFront", "Ch2BossFirstPhaseFront"), LayerType::UI);
	frontHpBarSprite->SetPosition({ 960.f, 90.f });
	frontHpBarSprite->SetScale({ 2.5f, 2.5f });

	topBackSprite->SetScale({ 3.f, 3.f });
	topBackSprite->SetPosition({ 960.f, 90.f });

	bottomBackSprite->SetScale({ 2.f, 2.5f });
	bottomBackSprite->SetPosition({ 960.f,95.f });

	nameText->SetString(L"레이아나 자매");
	tribeText->SetString(L"황금갈기기사단 부관");
	nameText->SetPosition({ 960.f, 60.f });
	tribeText->SetPosition({ 960.f, 135.f });

	reianaAHPBar = scene->AddGameObject(new HpBarUI("BossHealthBarFirstPhase", "ReianaAHealthBar"), LayerType::UI);
	reianaAHPBar->SetOrigin(Origins::MiddleLeft);
	reianaAHPBar->SetPosition({ 618.f, 102.f });
	reianaAHPBar->SetMaxHpBarSize({ 318.f,25.f });

	reianaBHPBar = scene->AddGameObject(new HpBarUI("BossHealthBarFirstPhase", "ReianaAHealthBar"), LayerType::UI);
	reianaBHPBar->SetOrigin(Origins::MiddleLeft);
	reianaBHPBar->SetPosition({ 985.f, 102.f });
	reianaBHPBar->SetMaxHpBarSize({ 318.f,25.f });
	

	bottomBackSprite->sortingOrder = 28;
	topBackSprite->sortingOrder = 28;
	frontHpBarSprite->sortingOrder = 26;

	reianaAHPBar->sortingOrder = 25;
	reianaBHPBar->sortingOrder = 25;
	sortingOrder = 24;
	nameText->sortingOrder = 23;
	tribeText->sortingOrder = 23;
}

void ReianaUIHub::ChangeHP(float currentHp, float maxHp)
{
	reianaAHPBar->ChangeHP(currentHp, maxHp);
	reianaBHPBar->ChangeHP(currentHp, maxHp);
}

void ReianaUIHub::ChangePhase()
{
	reianaBHPBar->SetActive(false);

	nameText->SetString(L"각성한 레이아나");
	reianaAHPBar->ChangeSprite("BossHealthBarSecondPhase");
	reianaAHPBar->ChangeSprite("BossHealthBarSecondPhase");

	bottomBackSprite->ChangeSprite("Ch2BossSecondPhaseTopBack");
	topBackSprite->ChangeSprite("Ch2BossSecondPhaseFront");
	frontHpBarSprite->ChangeSprite("Ch2BossSecondPhaseBottomBack");

	reianaAHPBar->SetMaxHpBarSize({ 822.f,25.f });
	reianaAHPBar->SetPosition({ 549.f, 90.f });
	frontHpBarSprite->SetPosition({ 960.f,80.f });
	bottomBackSprite->SetPosition({ 960.f, 75.f }); 
	topBackSprite->SetPosition({ 960.f, 75.f });

	nameText->SetPosition({ 955.f, 50.f });
	tribeText->SetPosition({ 955.f, 117.5f });
}

void ReianaUIHub::SetPosition(const sf::Vector2f& pos)
{
}