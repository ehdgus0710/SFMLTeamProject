#include "stdafx.h"
#include "UIRectangleShapeObject.h"

UIRectangleShapeObject::UIRectangleShapeObject(const std::string& texId, const std::string& name)
	: UIGameObject(name)
	, textureId(texId)
{
}


void UIRectangleShapeObject::SetPosition(const sf::Vector2f& pos)
{
	UIGameObject::SetPosition(pos);
	rectangleShape.setPosition(pos);
}

void UIRectangleShapeObject::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;
	rectangleShape.setSize(scale);
}

void UIRectangleShapeObject::SetRotation(float angle)
{
	rotation = angle;
	rectangleShape.setRotation(rotation);
}

void UIRectangleShapeObject::Render(sf::RenderWindow& renderWindow)
{
	renderWindow.draw(rectangleShape);
	UIGameObject::Render(renderWindow);
}

void UIRectangleShapeObject::Start()
{
	rectangleShape.setTexture(&ResourcesManager<sf::Texture>::GetInstance().Get(textureId));

	SetScale(scale);
	SetPosition(position);
	SetRotation(rotation);
	SetOrigin(originPreset);
}

void UIRectangleShapeObject::Update(const float& deltaTime)
{
	UIGameObject::Update(deltaTime);
}

void UIRectangleShapeObject::FixedUpdate(const float& deltaTime)
{
	UIGameObject::FixedUpdate(deltaTime);
}

void UIRectangleShapeObject::LateUpdate(const float& deltaTime)
{
	UIGameObject::LateUpdate(deltaTime);
}


void UIRectangleShapeObject::SetOrigin(Origins preset)
{
	originPreset = preset;
	origin = Utils::SetOrigin(rectangleShape, preset);
}

void UIRectangleShapeObject::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	rectangleShape.setOrigin(origin);
}


sf::FloatRect UIRectangleShapeObject::GetLocalBounds() const
{
    return rectangleShape.getLocalBounds();
}

sf::FloatRect UIRectangleShapeObject::GetGlobalBounds() const
{
    return rectangleShape.getGlobalBounds();
}