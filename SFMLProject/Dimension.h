#pragma once

class HitBoxObject;

class Dimension : public GameObject
{
protected:
	HitBoxObject* hitBox;
	sf::Sprite			sprite;

	sf::IntRect			textureUVRect;
	std::string			textureID ;
	sf::Vector2f		rectSize;
	sf::Vector2f		moveDirection;

	float				lifeTime;
	float				currentLifeTime;
public:
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
public:
	void Start() override;
	void Update(const float& deltaTime) override;
	void FixedUpdate(const float& deltaTime) override;
	void Render(sf::RenderWindow& renderWindow) override;

	void OnCollisionEnter(Collider* target) override;
	void CreateAnimator() override;

	sf::FloatRect GetLocalBounds() const;
	sf::FloatRect GetGlobalBounds() const;
	void OnCreateHitBox();
	void OnDestoryHitBox();
public:
	Dimension(ColliderLayer type, const std::string& texId, const std::string& name = "Dimension");
	virtual ~Dimension() = default;
	Dimension& operator= (const Dimension& other) = delete;
};

