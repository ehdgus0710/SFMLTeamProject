#include "stdafx.h"
#include "PlayerUIHub.h"
#include "Player.h"
#include "Scene.h"

#include "UITextGameObject.h"
#include "HpBarUI.h"

PlayerUIHub::PlayerUIHub(const std::string& texId, const std::string& name)
	: UISpriteGameObject(texId, name)
	, player(nullptr)
	, playerSimbolUI(nullptr)
	, hpText(nullptr)
	, maxHPText(nullptr)
	, playerHpBar(nullptr)
	, playerSkill2Frame(nullptr)
	, playerSkill1(nullptr)
	, playerSkill2(nullptr)
	, player2(nullptr)
	, subSkullSpriteUI(nullptr)
	, hpSlashText(nullptr)
	, subSkullFrame(nullptr)

{
}

void PlayerUIHub::ChangeHP(float currentHp, float maxHp)
{
	hpText->SetString(std::to_string((int)currentHp));
	maxHPText->SetString(std::to_string((int)maxHp));
	playerHpBar->ChangeHP(currentHp, maxHp);
}

void PlayerUIHub::ChangeSkull(Player* player)
{
	if (player == nullptr)
		return;

	this->player = player;

	if (player->GetFSM().FindStateType(PlayerStateType::Skill2))
	{
		playerSkill2Frame->SetActive(true);
		playerSkill2->SetActive(true);
	}
	else
	{
		playerSkill2Frame->SetActive(false);
		playerSkill2->SetActive(false);
	}
	ChangeSkillSprite(player->GetSkullType());
}

void PlayerUIHub::ChangeSkillSprite(SkullType type)
{
	switch (type)
	{
	case SkullType::Littlebone:
	{
		playerSkill1->ChangeSprite("SkullThrow");
		playerSkill2->ChangeSprite("Rebone");
	}
		break;
	case SkullType::End:
		break;
	default:
		break;
	}
}

void PlayerUIHub::AddSkull(Player* player)
{
	player2 = player;
	subSkullSpriteUI->SetActive(true);
	subSkullFrame->SetActive(true);
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

	// Player UI
	TEXTURE_MANAGER.Load("PlayerUiFrame", "graphics/UI/PlayerUI/player_ui_frame.png");
	TEXTURE_MANAGER.Load("SkulSimbul", "graphics/UI/PlayerUI/Skul.png");
	TEXTURE_MANAGER.Load("SkullThrow", "graphics/UI/PlayerUI/skull_throw.png");
	TEXTURE_MANAGER.Load("Rebone", "graphics/UI/PlayerUI/rebone.png");
	TEXTURE_MANAGER.Load("PlayerHealthBar", "graphics/UI/PlayerUI/Player_HealthBar.png");

	player = static_cast<Player*>(SceneManager::GetInstance().GetCurrentScene()->FindGameObject("Player", LayerType::Player));
	Scene* scene = SceneManager::GetInstance().GetCurrentScene();

	playerSimbolUI = scene->AddGameObject(new UISpriteGameObject("SkulSimbul", "MainSkulSimbul"), LayerType::UI);
	playerSimbolUI->SetPosition({ 100.f, 925.f });
	playerSimbolUI->SetScale({ 2.5f,2.5f });

	hpText = scene->AddGameObject(new UITextGameObject("Status", "hpText", 30), LayerType::UI);
	maxHPText = scene->AddGameObject(new UITextGameObject("Status", "maxHpText", 30), LayerType::UI);

	hpSlashText = scene->AddGameObject(new UITextGameObject("Status", "maxHpText", 30), LayerType::UI);

	maxHPText->SetString(std::to_string((int)player->GetCurrentHP()));
	hpText->SetString(std::to_string((int)player->GetCurrentHP()));
	hpSlashText->SetString("/");

	hpText->SetPosition({ 300.f, 1005.f });
	maxHPText->SetPosition({ 450.f, 1005.f });
	hpSlashText->SetPosition({ 375.f, 1005.f });

	playerHpBar = scene->AddGameObject(new HpBarUI("PlayerHealthBar", "PlayerHPBar"), LayerType::UI);
	playerHpBar->SetOrigin(Origins::MiddleLeft);
	playerHpBar->SetPosition({ 155.f, 1015.f });
	playerHpBar->SetMaxHpBarSize({ 405.f,30.f });
	playerHpBar->SetOwnerStatus(player->GetCurrentStatus());

	playerSkill2Frame = scene->AddGameObject(new UISpriteGameObject("SkulSkill2Frame", "SkulSkill2Frame"), LayerType::UI);
	playerSkill2Frame->SetPosition({ 350.f, 942.f });
	playerSkill2Frame->SetScale({ 3.5f, 3.5f });


	playerSkill1 = scene->AddGameObject(new UISpriteGameObject("", "SkulSkill1"), LayerType::UI);
	playerSkill1->SetPosition({ 245.f, 940.f });
	playerSkill1->SetScale({ 3.5f, 3.5f });

	playerSkill2 = scene->AddGameObject(new UISpriteGameObject("", "SkulSkill2"), LayerType::UI);
	playerSkill2->SetPosition({ 350.f, 940.f });
	playerSkill2->SetScale({ 3.5f, 3.5f });

	player->SetChangeHpAction(std::bind(&PlayerUIHub::ChangeHP, this, std::placeholders::_1, std::placeholders::_2));
	ChangeSkull(player);

	subSkullSpriteUI = scene->AddGameObject(new UISpriteGameObject("SkulSmallSimbul", "SkulSmallSimbul"), LayerType::UI);
	subSkullSpriteUI->SetPosition({ 50.f, 1000.f });
	subSkullSpriteUI->SetScale({ 2.5f,2.5f });

	subSkullFrame = scene->AddGameObject(new UISpriteGameObject("SubSkullFrame", "SubSkullFrame"), LayerType::UI);
	subSkullFrame->SetPosition({ 50.f, 1000.f });
	subSkullFrame->SetScale({ 2.5f,2.5f });
	if (player2 != nullptr)
	{
		subSkullSpriteUI->SetActive(true);
		subSkullFrame->SetActive(true);
	}
	else
	{
		subSkullSpriteUI->SetActive(false);
		subSkullFrame->SetActive(false);
	}

	playerHpBar->sortingOrder = 10;
	hpText->sortingOrder = 9;
	maxHPText->sortingOrder = 9;
	playerSimbolUI->sortingOrder = 7;
	subSkullFrame->sortingOrder = 6;
	subSkullSpriteUI->sortingOrder = 5;

}

void PlayerUIHub::Update(const float& deltaTime)
{
}