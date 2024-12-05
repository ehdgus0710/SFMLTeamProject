#pragma once

#include "ScrollButtonUI.h"

class SoundScrollObject : public ScrollButtonUI
{
protected:

public:
	void Start() override;
	void Update(const float& deltaTime) override;

	void OnCollisionEnter(Collider* target) override;
	void OnCollisionStay(Collider* target) override;
	void OnCollisionEnd(Collider* target) override;

public:
	SoundScrollObject(MoveType moveType, const std::string& textureID, const std::string& name);
	SoundScrollObject(MoveType moveType, const sf::Vector2f& startPosition, float minRange, float maxRange, const std::string& textureID, const std::string& name);
	virtual ~SoundScrollObject() = default;
	//UiTextureGameObject(const UiTextureGameObject& other) = delete;
	SoundScrollObject& operator= (const SoundScrollObject& other) = delete;
};

