#pragma once
class FireBullet : public GameObject
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

	void SetMoveDirection(const sf::Vector2f& direction) { moveDirection = direction; }
public:
	void Start() override;
	void Update(const float& deltaTime) override;
	void FixedUpdate(const float& deltaTime) override;
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

	// BlockSaveData GetBlockSaveDate() const;
	// void LoadBlockSaveData(const BlockSaveData& data);

public:
	FireBullet(const std::string& texId = "Items", const std::string& name = "FireBullet");
	virtual ~FireBullet() = default;
	FireBullet& operator= (const FireBullet& other) = delete;
};

