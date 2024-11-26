#pragma once
#include "GameObject.h"
class TriggerObject : public GameObject
{
protected:
	std::vector<std::function<void()>> triggerEvents;
	sf::RectangleShape	render;
	sf::Vector2f		restartPosition;

public:
	void AddEnterEvenet(std::function<void()> enterEvent) { triggerEvents.push_back(enterEvent); }

public:
	void SetScale(const sf::Vector2f& scale) override;
	void SetRotation(float angle) override;
	void SetPosition(const sf::Vector2f& pos) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;
public:
	void Start() override;
	void Render(sf::RenderWindow& renderWindow) override;

	void OnCollisionEnter(Collider* target) override;

	sf::FloatRect GetLocalBounds() const;
	sf::FloatRect GetGlobalBounds() const;
public:
	TriggerObject(const std::string& name = "TriggerObject");
	virtual ~TriggerObject() = default;
	TriggerObject& operator= (const TriggerObject& other) = delete;
};

