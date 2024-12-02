#include "stdafx.h"
#include "YggdrasilUIHub.h"

#include "Scene.h"
#include "UITextGameObject.h"
#include "HpBarUI.h"
#include "Yggdrasil.h"

YggdrasilUIHub::YggdrasilUIHub(const std::string& texId, const std::string& name)
	: UISpriteGameObject(texId, name)
	, hpBarSprite(nullptr)
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
	hpBarSprite->ChangeSprite("YggdrasilSecondPhaseTop");
	hpBar->ChangeSprite("YggdrasilSecondPhaseBottomBack");
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
	topBackSprite->SetPosition({ 960.f,140.f});

	bottomBackSprite->SetScale({ 2.f, 2.5f });
	bottomBackSprite->SetPosition({ 960.f,125.f });

	nameText->SetString(L"위그드라실");
	tribeText->SetString(L"엘로 장로");
	nameText->SetPosition({ 960.f, 105.f });
	tribeText->SetPosition({ 960.f, 165.f });

	hpBar = scene->AddGameObject(new HpBarUI("BossHealthBarFirstPhase", "BossHealthBar"), LayerType::UI);
	hpBar->SetOrigin(Origins::MiddleLeft);
	hpBar->SetPosition({ 618.f, 138.f });
	hpBar->SetMaxHpBarSize({ 685.f,25.f });
	
	hpBarSprite = scene->AddGameObject(new UISpriteGameObject("YggdrasilFirstPhaseFront", "YggdrasilFront"), LayerType::UI);
	hpBarSprite->SetPosition({ 960.f, 125.f });
	hpBarSprite->SetScale({ 2.5f, 2.5f });

	bottomBackSprite->sortingOrder = 8;
	topBackSprite->sortingOrder = 8;
	hpBarSprite->sortingOrder = 6;
	hpBar->sortingOrder = 5;
	sortingOrder = 4;
	nameText->sortingOrder = 3;
	nameText->sortingOrder = 3;

}
void YggdrasilUIHub::Update(const float& deltaTime)
{
}