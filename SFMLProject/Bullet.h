#pragma once

#include "HitBoxObject.h"

class Bullet : public HitBoxObject
{
protected:
	sf::Sprite			sprite;

	sf::IntRect			textureUVRect;
	std::string			textureID;
	sf::Vector2f		rectSize;
	sf::Vector2f		moveDirection;

	float				lifeTime;
	float				currentLifeTime;
	float				speed;
	bool				isShoot;

public:
	void Shoot();

	void SetUVRect(const sf::IntRect uvRect);
	void SetScale(const sf::Vector2f& scale) override;
	void SetRotation(float angle) override;
	void SetPosition(const sf::Vector2f& pos) override;

	sf::Vector2f GetScale() const override;

	virtual sf::IntRect GetTextureUVRect() { return textureUVRect; }
	virtual sf::Vector2f GetRectSize() { return rectSize; }
	const std::string& GetTextureID() const { return textureID; }

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void SetMoveDirection(const sf::Vector2f& direction);
	void SetSpeed(float speed) { this->speed = speed; }
	float GetSpeed() { return speed; }

public:
	void Start() override;
	void Update(const float& deltaTime) override;
	void Render(sf::RenderWindow& renderWindow) override;

	void OnCollisionEnter(Collider* target) override;
	void CreateAnimator() override;

	sf::FloatRect GetLocalBounds() const;
	sf::FloatRect GetGlobalBounds() const;
public:
	bool Save() const override;
	bool Load() override;
	bool SaveCsv(const std::string& filePath) const override;
	bool LoadCsv(const std::string& filePath) override;

public:
	Bullet(GameObject* owner, ColliderLayer thisLayerType, ColliderLayer targetLayer, const std::string& texId, const std::string& name = "Bullet");
	virtual ~Bullet() = default;
	Bullet& operator= (const Bullet& other) = delete;
};

