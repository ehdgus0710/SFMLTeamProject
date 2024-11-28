#pragma once
#include "GameObject.h"
class AnimationGameObject : public GameObject
{
protected:
	sf::Sprite		sprite;
	bool			isFlipX;

public:
	void SetPosition(const sf::Vector2f& pos) override;
	void SetScale(const sf::Vector2f& scale) override;
	void SetRotation(float angle) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;
public:
	void OnFlipX();
	bool IsFlipX() { return isFlipX; }

	void CreateAnimator() override;

public:
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void FixedUpdate(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;
	void Render(sf::RenderWindow& renderWindow) override;

	sf::FloatRect GetLocalBounds() const;
	sf::FloatRect GetGlobalBounds() const;
public:
	AnimationGameObject(const std::string& name = "AnimationGameObject");
	virtual ~AnimationGameObject();
	AnimationGameObject& operator= (const AnimationGameObject& other) = delete;
};

