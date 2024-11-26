#include "stdafx.h"
#include "UIGameObject.h"

UIGameObject::UIGameObject(const std::string& name)
	: GameObject(name)
{
}

void UIGameObject::Awake()
{
	GameObject::Awake();
}

void UIGameObject::Start()
{
	GameObject::Start();
}

void UIGameObject::Update(const float& deltaTime)
{
	GameObject::Update(deltaTime);
}

void UIGameObject::FixedUpdate(const float& deltaTime)
{
	GameObject::FixedUpdate(deltaTime);
}

void UIGameObject::LateUpdate(const float& deltaTime)
{
	GameObject::LateUpdate(deltaTime);
}

void UIGameObject::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
}

void UIGameObject::SetOrigin(const sf::Vector2f& newOrigin)
{
	GameObject::SetOrigin(newOrigin);
}

void UIGameObject::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
}

void UIGameObject::Render(sf::RenderWindow& window)
{
	GameObject::Render(window);
}