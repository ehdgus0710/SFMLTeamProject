#pragma once
#include "GameObject.h"
#include "WallCollisionSaveData.h"

class WallCollisionObject : public GameObject
{
protected:
	static int wallID;

public:
	void SetScale(const sf::Vector2f& scale) override;
	void SetPosition(const sf::Vector2f& pos) override;
	void SetOrigin(Origins preset) override;
	sf::FloatRect GetLocalBounds() const override;
	sf::FloatRect GetGlobalBounds() const override;

public:
	void Start() override;

	virtual void OnCollisionEnter(Collider* target);
	virtual void OnCollisionStay(Collider* target);
	virtual void OnCollisionEnd(Collider* target);

public:
	bool Save() const override;
	bool Load() override;
	bool SaveCsv(const std::string& filePath) const override;
	bool LoadCsv(const std::string& filePath) override;
	WallCollisionSaveData GetWallCollisionSaveData() const;
	void LoadWallCollisionSaveData(const WallCollisionSaveData& data);
public:
	WallCollisionObject(const std::string& name = "Wall");
	virtual ~WallCollisionObject();

};

