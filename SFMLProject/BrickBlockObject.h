#pragma once
#include "BlockObject.h"
class BrickBlockObject : public BlockObject
{
protected:
	sf::Vector2f	startPosition;
	sf::Vector2f	endPosition;
	float			hitMoveDistance;
	float			moveSpeed;

	float			currentMoveTime;
	bool			isReturn;
	bool			isHit;

public:
	void OnBreak();
	void OnHitMove();

public:
	void Update(const float& deltaTime) override;

	void OnCollisionEnter(Collider* target) override;
	void OnCollisionStay(Collider* target) override;
	void OnCollisionEnd(Collider* target) override;

public:
	bool Save() const override;
	bool Load() override;
public:
	BrickBlockObject(const std::string& texId, const std::string& name = "BrickBlock");
	virtual ~BrickBlockObject() = default;
	BrickBlockObject& operator= (const BrickBlockObject& other) = delete;
};

