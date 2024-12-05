#pragma once

#include "UISpriteGameObject.h"

enum class MoveType
{
	LeftRight,
	UpDown,
	End
};

class ScrollButtonUI : public UISpriteGameObject
{
protected:
	UISpriteGameObject* dotSpriteObject;

	MoveType		moveType;
	GameObject*		followTargetObject;
	sf::Vector2f	minPosition;
	sf::Vector2f	scrollRectSize;

	float			currentValue;

	std::vector<std::function<void()>>		buttonCollsionEnterEvents;
	std::vector<std::function<void()>>		buttonCollsionStayEvents;
	std::vector<std::function<void()>>		buttonCollsionEndClickEvents;
	std::vector<std::function<void(float)>> changeValueEvents;
public:
	void SetButtonClickStayEvent(std::function<void()> buttonEvent) { buttonCollsionStayEvents.push_back(buttonEvent); }
	void SetButtonClickEnterEvent(std::function<void()> buttonEvent) { buttonCollsionEnterEvents.push_back(buttonEvent); }
	void SetButtonClickEndEvent(std::function<void()> buttonEvent) { buttonCollsionEndClickEvents.push_back(buttonEvent); }
	void SetChangeValueEvent(std::function<void(float)> buttonEvent) { changeValueEvents.push_back(buttonEvent); }

	void SetStartInfo(const sf::Vector2f& startPosition, const sf::Vector2f rectSize, float startValue = 50.f);
	void ChangeSpriteDot(const std::string& textureId);
	float GetCurrentPercent();

public:
	void Start() override;
	void SetActive(const bool active) override;
	void Update(const float& deltaTime) override;

	void OnCollisionEnter(Collider* target) override;
	void OnCollisionStay(Collider* target) override;
	void OnCollisionEnd(Collider* target) override;

public:
	ScrollButtonUI(MoveType moveType, const std::string& textureID, const std::string& name);
	ScrollButtonUI(MoveType moveType,const sf::Vector2f& startPosition, float minRange, float maxRange, const std::string& textureID, const std::string& name);
	virtual ~ScrollButtonUI() = default;
	//UiTextureGameObject(const UiTextureGameObject& other) = delete;
	ScrollButtonUI& operator= (const ScrollButtonUI& other) = delete;
};

