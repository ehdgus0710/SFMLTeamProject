#pragma once
#include "ItemObject.h"

class MushRoomObject : public ItemObject
{
private:
	sf::Vector2f		moveDirection;
	float				moveSpeed;

public:
	void Start() override;
	void FixedUpdate(const float& deltaTime) override;

	void OnCollisionEnter(Collider* target) override;
	void OnCollisionStay(Collider* target) override;
	void OnCollisionEnd(Collider* target) override;
public:
	MushRoomObject();
	~MushRoomObject() = default;
};

