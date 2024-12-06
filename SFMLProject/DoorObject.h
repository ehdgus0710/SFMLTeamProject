#pragma once

#include "AnimationGameObject.h"
class UITextGameObject;
class UISpriteGameObject;

class DoorObject : public AnimationGameObject
{
protected:
	UITextGameObject*		interactionText;
	UISpriteGameObject*		interactionKeySprite;
	sf::Vector2f			textPosition;
	sf::Vector2f			keyPosition;

	SceneIds				changeSceneIds;
public:
	void SetPosition(const sf::Vector2f& pos) override;
	void SetScale(const sf::Vector2f& scale) override;
	void SetRotation(float angle) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;
public:
	void Awake() override;
	void Start() override;
	void Render(sf::RenderWindow& renderWindow) override;

	void OnCollisionEnter(Collider* target) override;
	void OnCollisionStay(Collider* target) override;
	void OnCollisionEnd(Collider* target) override;
public:
	DoorObject(const std::string& keyTextureID, SceneIds changeSceneId, const std::string& name = "DoorObject");
	virtual ~DoorObject();
	DoorObject& operator= (const DoorObject& other) = delete;
};

