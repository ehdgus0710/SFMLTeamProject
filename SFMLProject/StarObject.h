#pragma once

#include "ItemObject.h"

class StarObject : public ItemObject
{
private:
	sf::Vector2f		moveDirection;
	float				moveSpeed;

	float				lifeTime;
	float				currentLifeTime;

	bool				isJump;

public:
	void Start() override;
	void Update(const float& deltaTime) override;
	void FixedUpdate(const float& deltaTime) override;

	void OnCollisionEnter(Collider* target) override;
	void OnCollisionStay(Collider* target) override;
	void OnCollisionEnd(Collider* target) override;
	void CreateAnimator() override;
public:
	StarObject();
	~StarObject() = default;
};

