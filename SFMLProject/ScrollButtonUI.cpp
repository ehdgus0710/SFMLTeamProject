#include "stdafx.h"
#include "ScrollButtonUI.h"
#include "Collider.h"

ScrollButtonUI::ScrollButtonUI(MoveType moveType, const std::string& textureID, const std::string& name)
	: UISpriteGameObject(textureID, name)
	, moveType(moveType)
	, followTargetObject(nullptr)
	, dotSpriteObject(nullptr)
	, currentValue(0.f)

{
	CreateCollider(ColliderType::Rectangle, ColliderLayer::UI);
}

ScrollButtonUI::ScrollButtonUI(MoveType moveType, const sf::Vector2f& startPosition, float minRange, float maxRange, const std::string& textureID, const std::string& name)
	: UISpriteGameObject(textureID, name)
	, moveType(moveType)
	, followTargetObject(nullptr)
	, dotSpriteObject(nullptr)
	, currentValue(0.f)

{
	position = startPosition;
	CreateCollider(ColliderType::Rectangle, ColliderLayer::UI);
}

void ScrollButtonUI::SetStartInfo(const sf::Vector2f& startPosition, const sf::Vector2f rectSize, float startValue)
{
	scrollRectSize = rectSize;
	collider->SetScale(scrollRectSize);
	position = startPosition;
	this->minPosition = position;

	if (moveType == MoveType::LeftRight)
	{
		this->minPosition.x -= collider->GetScale().x * 0.5f;
		startValue = Utils::Clamp(startValue, 0.f, collider->GetScale().x);
		//position.x = minPosition.x + startValue;
	}
	else
	{
		this->minPosition.y -= collider->GetScale().y * 0.5f;
		startValue = Utils::Clamp(startValue, 0.f, collider->GetScale().y);
		// position.y = minPosition.y + startValue;
	}

	currentValue = startValue;

	if (dotSpriteObject == nullptr)
	{
		Scene* currentScene = SceneManager::GetInstance().GetCurrentScene();
		dotSpriteObject = currentScene->AddGameObject(new UISpriteGameObject("OptionsAudioDot", "button"), LayerType::UI);
		dotSpriteObject->SetPosition({ this->minPosition.x + currentValue * scrollRectSize.x * 0.01f , this->minPosition.y });
		dotSpriteObject->SetScale({ 3.f,3.f });
		dotSpriteObject->SetOrigin(Origins::MiddleCenter);
	}

}

void ScrollButtonUI::ChangeSpriteDot(const std::string& texId)
{
	dotSpriteObject->ChangeSprite(texId);
}

float ScrollButtonUI::GetCurrentPercent()
{
	if (moveType == MoveType::LeftRight)
	{
		float percent = dotSpriteObject->GetPosition().x - minPosition.x;
		return (percent / scrollRectSize.x) * 100.f;
	}
	else
	{
		float percent = dotSpriteObject->GetPosition().y - minPosition.y;
		return (percent / scrollRectSize.y) * 100.f;
	}
}

void ScrollButtonUI::Start()
{
	UISpriteGameObject::Start();
	collider->Reset();

	sortingOrder = 4;
	dotSpriteObject->sortingOrder = 3;
}

void ScrollButtonUI::SetActive(const bool active)
{
	UISpriteGameObject::SetActive(active);
	dotSpriteObject->SetActive(active);
}

void ScrollButtonUI::Update(const float& deltaTime)
{
	if (followTargetObject != nullptr)
	{
		if (InputManager::GetInstance().GetKeyPressed(sf::Mouse::Left))
		{
			sf::Vector2f dotPos = dotSpriteObject->GetPosition();
			dotPos.x = Utils::Clamp(followTargetObject->GetPosition().x, minPosition.x, minPosition.x + scrollRectSize.x);
			dotSpriteObject->SetPosition(dotPos);

			 for (auto& changeEvent : changeValueEvents)
			 {
				 if (changeEvent)
					 changeEvent(GetCurrentPercent());
			 }
		}
		else
		{
			followTargetObject = nullptr;
		}
	}
}

void ScrollButtonUI::OnCollisionEnter(Collider* target)
{
	for (auto& enterEvent : buttonCollsionEnterEvents)
	{
		if (enterEvent)
			enterEvent();
	}
}

void ScrollButtonUI::OnCollisionStay(Collider* target)
{
	if (InputManager::GetInstance().GetKeyDown(sf::Mouse::Left))
	{
		followTargetObject = target->GetOwner();
	}

	for (auto& stayEvent : buttonCollsionStayEvents)
	{
		if (stayEvent)
			stayEvent();
	}
}

void ScrollButtonUI::OnCollisionEnd(Collider* target)
{
	for (auto& endEvent : buttonCollsionEndClickEvents)
	{
		if (endEvent)
			endEvent();
	}
}