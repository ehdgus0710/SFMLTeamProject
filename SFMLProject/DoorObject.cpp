#include "stdafx.h"
#include "DoorObject.h"

#include "UITextGameObject.h"
#include "UISpriteGameObject.h"
#include "Scene.h"
#include "Animator.h"
#include "Animation.h"
#include "Collider.h"
#include "Stage1.h"
#include "Stage2.h"
#include "Stage3.h"

DoorObject::DoorObject(const std::string& keyTextureID, SceneIds changeSceneId, const std::string& name)
	: AnimationGameObject(name)
	, interactionText(nullptr)
	, interactionKeySprite(nullptr)
	, changeSceneIds(changeSceneId)
{
	ResourcesManager<sf::Font>::GetInstance().Load("NameFont", "fonts/D2Coding.ttc", true);
	TEXTURE_MANAGER.Load("KeyF", "graphics/UI/Key/F.png");

	ResourcesManager<sf::Texture>::GetInstance().Load("Bossidle", "graphics/objects/bossidle.png", true);

	CreateCollider(ColliderType::Rectangle, ColliderLayer::Door);
	CreateAnimator();
	animator->AddAnimation(new Animation("animations/Objects/bossDoorIdle.csv"), "bossDoorIdle");

	Scene* currentScene = SceneManager::GetInstance().GetCurrentScene();
	interactionText = currentScene->AddGameObject(new UITextGameObject("NameFont", name + "Text", 30), LayerType::Effect);
	interactionText->SetString(L"들어가기");
	interactionText->Start();

	interactionKeySprite = currentScene->AddGameObject(new UISpriteGameObject(keyTextureID, name + "Sprite"), LayerType::Effect);
	interactionKeySprite->Start();

	textPosition = sf::Vector2f::down * 260.f;
	keyPosition = sf::Vector2f::down * 260.f + sf::Vector2f::left * 100.f;
	scale = { 3.f,3.f };

	collider->SetScale({ 100.f, 100.f });
	collider->SetOffsetPosition({ -20.f, 80.f });
	InputManager::GetInstance().BindKey(sf::Keyboard::F);
}

DoorObject::~DoorObject()
{
}

void DoorObject::SetPosition(const sf::Vector2f& pos)
{
	AnimationGameObject::SetPosition(pos);
	interactionText->SetPosition(pos + textPosition);
	interactionKeySprite->SetPosition(pos + keyPosition);
}

void DoorObject::SetScale(const sf::Vector2f& scale)
{
	AnimationGameObject::SetScale(scale);
	interactionText->SetScale(scale);
	interactionKeySprite->SetScale(scale);
}

void DoorObject::SetRotation(float angle)
{
	AnimationGameObject::SetRotation(angle);
	interactionText->SetRotation(angle);
	interactionKeySprite->SetRotation(angle);
}

void DoorObject::SetOrigin(Origins preset)
{
	AnimationGameObject::SetOrigin(preset);
	interactionText->SetOrigin(preset);
	interactionKeySprite->SetOrigin(preset);
}

void DoorObject::SetOrigin(const sf::Vector2f& newOrigin)
{
	AnimationGameObject::SetOrigin(newOrigin);
	interactionText->SetOrigin(newOrigin);
	interactionKeySprite->SetOrigin(newOrigin);
}

void DoorObject::Awake()
{
	AnimationGameObject::Awake();
}

void DoorObject::Start()
{
	AnimationGameObject::Start();

	interactionText->SetActive(false);
	interactionKeySprite->SetActive(false);
	animator->ChangeAnimation("bossDoorIdle", true);
}

void DoorObject::Render(sf::RenderWindow& renderWindow)
{
	AnimationGameObject::Render(renderWindow);
}

void DoorObject::OnCollisionEnter(Collider* target)
{
	if (target->GetColliderLayer() == ColliderLayer::Player)
	{
		interactionText->SetActive(true);
		interactionKeySprite->SetActive(true);
	}
}

void DoorObject::OnCollisionStay(Collider* target)
{
	if (target->GetColliderLayer() == ColliderLayer::Player)
	{
		if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::F))
		{
			SceneManager::GetInstance().GetCurrentScene()->SetChangeScene(changeSceneIds);
		}
	}
}

void DoorObject::OnCollisionEnd(Collider* target)
{
	if (target->GetColliderLayer() == ColliderLayer::Player)
	{
		interactionText->SetActive(false);
		interactionKeySprite->SetActive(false);
	}
}
