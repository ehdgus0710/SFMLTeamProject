#pragma once

#include "SpriteGameObject.h"
#include "KooparScaffoldingObject.h"

class WallCollisionObject;

class LabberObject : public SpriteGameObject
{
private:
	sf::IntRect textureRect;
	std::vector<KooparScaffoldingObject*> scaffoldingObjects;

public:
	void Start() override;
	void SetScale(const sf::Vector2f& scale) override;
	void OnCollisionEnter(Collider* target) override;
public:
	LabberObject(const sf::IntRect& textureRect, const std::string& texId, const std::string& name = "");
	virtual ~LabberObject() = default;
};

