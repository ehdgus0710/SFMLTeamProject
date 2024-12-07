#include "stdafx.h"
#include "MouseObject.h"
#include "Collider.h"

MouseObject::MouseObject(const std::string& name)
	: GameObject(name)
{
	CreateCollider(ColliderType::Point, ColliderLayer::UI);
}

void MouseObject::Awake()
{
	GameObject::Awake();
}

void MouseObject::Start()
{
	SetScale(scale);
	SetPosition(position);
	SetRotation(rotation);
	SetOrigin(originPreset);
	collider->Reset();
}

void MouseObject::Update(const float& deltaTime)
{
	if(layerType == LayerType::UI || layerType == LayerType::InGameUI)
		SetPosition(SceneManager::GetInstance().GetCurrentScene()->ScreenToUI(InputManager::GetInstance().GetMousePosition()));
	else
		SetPosition(SceneManager::GetInstance().GetCurrentScene()->ScreenToWorld(InputManager::GetInstance().GetMousePosition()));
}
void MouseObject::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
}

void MouseObject::SetOrigin(const sf::Vector2f& newOrigin)
{
	GameObject::SetOrigin(newOrigin);
}

void MouseObject::OnCollisionEnter(Collider* target)
{
}

void MouseObject::OnCollisionStay(Collider* target)
{
}

sf::FloatRect MouseObject::GetLocalBounds() const
{
	return sf::FloatRect(position, sf::Vector2f::one);
}

sf::FloatRect MouseObject::GetGlobalBounds() const
{
	return sf::FloatRect(position, sf::Vector2f::one);
}

void MouseObject::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	collider->SetPosition(position);
}

void MouseObject::Render(sf::RenderWindow& window)
{
	GameObject::Render(window);
}