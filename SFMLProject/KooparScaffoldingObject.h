#pragma once

#include "SpriteGameObject.h"
class KooparScaffoldingObject : public SpriteGameObject
{
private:
	sf::IntRect textureRect;

public:
	void Start() override;
	void SetScale(const sf::Vector2f& scale) override;
public:
	KooparScaffoldingObject(const std::string& texId, const std::string& name = "");
	virtual ~KooparScaffoldingObject() = default;
};

