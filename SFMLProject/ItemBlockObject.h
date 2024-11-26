#pragma once
#include "BlockObject.h"

class ItemBlockObject : public BlockObject
{
protected:
	sf::IntRect		changeTextureUvRect;

	ItemType		itemType;
	int				itemCount;

	sf::Vector2f	startPosition;
	sf::Vector2f	endPosition;

	float			hitMoveDistance;
	float			moveSpeed;

	float			currentMoveTime;
	bool			isReturn;
	bool			isHit;

public:
	virtual void SetChangeTextureUvRect(const sf::IntRect uvRect) { changeTextureUvRect = uvRect; }
	virtual sf::IntRect GetChangeTextureUvRect() { return changeTextureUvRect; }

	void SetItemType(ItemType type) { itemType = type; }
	ItemType GetItemType() { return itemType; }

	void OnChangetRectUV();
	void OnHitMove();
	void CreateItem();

public:
	void Update(const float& deltaTime) override;
	void OnCollisionEnter(Collider* target) override;
	void OnCollisionStay(Collider* target) override;
	void OnCollisionEnd(Collider* target) override;

	bool Save() const override;
	bool Load() override;
	bool SaveCsv(const std::string& filePath) const override;
	bool LoadCsv(const std::string& filePath) override;

	ItemBlockSaveData GetItemBlockSaveData() const;
	void LoadItemBlockSaveData(const ItemBlockSaveData& data);
public:
	ItemBlockObject(ItemType type, const std::string& texId, const std::string& changeTexId, const std::string& name = "ItemBlock");
	virtual ~ItemBlockObject() = default;
	ItemBlockObject& operator= (const ItemBlockObject& other) = delete;
};

