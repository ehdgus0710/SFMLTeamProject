#include "stdafx.h"
#include "ReianaUIHub.h"
#include "UITextGameObject.h"
#include "HpBarUI.h"

#include "Reiana.h"
#include "B_Reiana.h"
#include "AwakeReiana.h"



ReianaUIHub::ReianaUIHub(const std::string& texId, const std::string& name)
	: UISpriteGameObject(texId, name)
	, topBackSprite(nullptr)
	, bottomBackSprite(nullptr)
	, frontHpBarSprite(nullptr)
	, reianaAHPBar(nullptr)
	, reianaBHPBar(nullptr)
	, nameText(nullptr)
	, tribeText(nullptr)
	, reianaA(nullptr)
	, reianaB(nullptr)
	, awakeReiana(nullptr)

{
}

void ReianaUIHub::Start()
{
	UISpriteGameObject::Start();

	Scene* scene = SceneManager::GetInstance().GetCurrentScene();

	reianaA = static_cast<Reiana*>(SceneManager::GetInstance().GetCurrentScene()->FindGameObject("Reiana", LayerType::Boss));
	reianaB = static_cast<B_Reiana*>(SceneManager::GetInstance().GetCurrentScene()->FindGameObject("b_Reiana", LayerType::Boss));
	

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

	awakenReianaHPBar = scene->AddGameObject(new HpBarUI("BossHealthBarSecondPhase", "AwakenReianaHPBar"), LayerType::UI);
	awakenReianaHPBar->SetOrigin(Origins::MiddleLeft);

	awakenReianaHPBar->SetMaxHpBarSize({ 822.f,25.f });
	awakenReianaHPBar->SetPosition({ 549.f, 90.f });
	
	reianaA->SetChangeHpAction(std::bind(&ReianaUIHub::ChangeReianaAHP, this, std::placeholders::_1, std::placeholders::_2));
	reianaA->SetReianaUIHub(this);
	reianaB->SetChangeHpAction(std::bind(&ReianaUIHub::ChangeReianaBHP, this, std::placeholders::_1, std::placeholders::_2));
	reianaB->SetReianaUIHub(this);

	awakenReianaHPBar->SetActive(false);

	bottomBackSprite->sortingOrder = 28;
	topBackSprite->sortingOrder = 28;
	frontHpBarSprite->sortingOrder = 26;

	reianaAHPBar->sortingOrder = 25;
	reianaBHPBar->sortingOrder = 25;
	sortingOrder = 24;
	nameText->sortingOrder = 23;
	tribeText->sortingOrder = 23;
}

void ReianaUIHub::ChangeReianaAHP(float currentHp, float maxHp)
{
	reianaAHPBar->ChangeHP(currentHp, maxHp);
}

void ReianaUIHub::ChangeReianaBHP(float currentHp, float maxHp)
{
	reianaBHPBar->ChangeHP(currentHp, maxHp);
}

void ReianaUIHub::ChangeAwakenReianaHP(float currentHp, float maxHp)
{
	awakenReianaHPBar->ChangeHP(currentHp, maxHp);
}

void ReianaUIHub::ChangePhase()
{
	reianaBHPBar->SetActive(false);
	reianaAHPBar->SetActive(false);
	awakenReianaHPBar->SetActive(true);

	awakeReiana->SetChangeHpAction(std::bind(&ReianaUIHub::ChangeAwakenReianaHP, this, std::placeholders::_1, std::placeholders::_2));

	nameText->SetString(L"각성한 레이아나");
	reianaAHPBar->ChangeSprite("BossHealthBarSecondPhase");

	bottomBackSprite->ChangeSprite("Ch2BossSecondPhaseTopBack");
	topBackSprite->ChangeSprite("Ch2BossSecondPhaseFront");
	frontHpBarSprite->ChangeSprite("Ch2BossSecondPhaseBottomBack");

	frontHpBarSprite->SetPosition({ 960.f,80.f });
	bottomBackSprite->SetPosition({ 960.f, 75.f }); 
	topBackSprite->SetPosition({ 960.f, 75.f });

	nameText->SetPosition({ 955.f, 50.f });
	tribeText->SetPosition({ 955.f, 117.5f });
}

void ReianaUIHub::OnDeadReiana()
{
	topBackSprite->OnDestory();
	bottomBackSprite->OnDestory();
	frontHpBarSprite->OnDestory();
	reianaAHPBar->OnDestory();
	reianaBHPBar->OnDestory();
	awakenReianaHPBar->OnDestory();
	nameText->OnDestory();
	tribeText->OnDestory();
	OnDestory();
}
