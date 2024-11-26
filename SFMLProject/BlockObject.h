#pragma once

#include "GameObject.h"
#include "BlockSaveData.h"

class Player;

class BlockObject : public GameObject
{
protected:
	sf::RectangleShape	render;
	BlockType			blockType;
	Player*				player;

	sf::IntRect			textureUVRect;
	sf::Vector2f		rectSize;
	std::string			textureID;

public:

	virtual void SetUVRect(const sf::IntRect uvRect);
	void SetScale(const sf::Vector2f& scale) override;
	void SetRotation(float angle) override;
	void SetPosition(const sf::Vector2f& pos) override;
	sf::Vector2f GetScale() const override;

	void SetSize(const sf::Vector2f& size);
	virtual sf::IntRect GetTextureUVRect() { return textureUVRect; }
	virtual sf::Vector2f GetRectSize() { return rectSize; }

	const std::string& GetTextureID() const { return textureID; }

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	BlockType GetBlockType() { return blockType; }
public:
	void Start() override;
	void Render(sf::RenderWindow& renderWindow) override;

	void OnCollisionEnter(Collider* target) override;
	void OnCollisionStay(Collider* target) override;
	void OnCollisionEnd(Collider* target) override;

	sf::FloatRect GetLocalBounds() const;
	sf::FloatRect GetGlobalBounds() const;
public:
	bool Save() const override;
	bool Load() override;
	bool SaveCsv(const std::string& filePath) const override;
	bool LoadCsv(const std::string& filePath) override;

	BlockSaveData GetBlockSaveDate() const;
	void LoadBlockSaveData(const BlockSaveData& data);

public:
	BlockObject(BlockType type, const std::string& texId, const std::string& name = "Block");
	virtual ~BlockObject() = default;
	BlockObject& operator= (const BlockObject& other) = delete;
};

