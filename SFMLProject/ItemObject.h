#pragma once
class ItemObject : public GameObject
{
protected:
	sf::Sprite			sprite;
	ItemType			itemType;

	sf::IntRect			textureUVRect;
	std::string			textureID;
	sf::Vector2f		rectSize;
	sf::Vector2f		createEndPosition;

	float				speed;
	bool				isCreateEvent;

public:
	void SetUVRect(const sf::IntRect uvRect);
	void SetScale(const sf::Vector2f& scale) override;
	void SetRotation(float angle) override;
	void SetPosition(const sf::Vector2f& pos) override;
	
	virtual void CreateEvenet();
	
	sf::Vector2f GetScale() const override;

	virtual sf::IntRect GetTextureUVRect() { return textureUVRect; }
	virtual sf::Vector2f GetRectSize() { return rectSize; }

	const std::string& GetTextureID() const { return textureID; }

	void Start() override;
	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

public:
	void Update(const float& deltaTime) override;
	void Render(sf::RenderWindow& renderWindow) override;

	void OnCollisionEnter(Collider* target) override;

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
	ItemObject(ItemType type, const std::string& texId, const std::string& name = "Item");
	virtual ~ItemObject() = default;
	ItemObject& operator= (const ItemObject& other) = delete;
};

