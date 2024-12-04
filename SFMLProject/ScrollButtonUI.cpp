#include "stdafx.h"
#include "ScrollButtonUI.h"
#include "Collider.h"

ScrollButtonUI::ScrollButtonUI(MoveType moveType, const std::string& textureID, const std::string& name)
	: UISpriteGameObject(textureID, name)
	, moveType(moveType)
	, followTargetObject(nullptr)
	, minRange(0.f)
	, maxRange(100.f)
{
	CreateCollider(ColliderType::Rectangle, ColliderLayer::UI);
}

ScrollButtonUI::ScrollButtonUI(MoveType moveType, const sf::Vector2f& startPosition, float minRange, float maxRange, const std::string& textureID, const std::string& name)
	: UISpriteGameObject(textureID, name)
	, moveType(moveType)
	, followTargetObject(nullptr)
	, minRange(minRange)
	, maxRange(maxRange) 
{
	position = startPosition;
	CreateCollider(ColliderType::Rectangle, ColliderLayer::UI);
}


void ScrollButtonUI::SetStartPosition(const sf::Vector2f& minPosition, float minValue, float maxValue, float startValue)
{
	position = minPosition;
	this->minPosition = position;
	minRange = minValue;
	maxRange = maxValue;

	startValue = Utils::Clamp(startValue, minRange, maxRange);

	if (moveType == MoveType::LeftRight)
		position.x += startValue;
	else
		position.y += startValue;
}

float ScrollButtonUI::GetCurrentPercent()
{
	if (moveType == MoveType::LeftRight)
	{
		float percent = position.x - minPosition.x;
		return (percent / maxRange) * 100.f;
	}
	else
	{
		float percent = position.y - minPosition.y;
		return (percent / maxRange) * 100.f;
	}
}

void ScrollButtonUI::Start()
{
	UISpriteGameObject::Start();
	collider->Reset();
}

void ScrollButtonUI::Update(const float& deltaTime)
{
	if (followTargetObject != nullptr)
	{
		if (InputManager::GetInstance().GetKeyPressed(sf::Mouse::Left))
		{
			 position.x = Utils::Clamp(followTargetObject->GetPosition().x, minPosition.x, minPosition.x + maxRange);
			 SetPosition(position);

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