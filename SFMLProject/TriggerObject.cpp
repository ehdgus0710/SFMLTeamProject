#include "stdafx.h"
#include "TriggerObject.h"
#include "Collider.h"

TriggerObject::TriggerObject(const std::string& name) 
    : GameObject(name)
{
    CreateCollider(ColliderType::Rectangle, ColliderLayer::SavePoint);
}

void TriggerObject::SetScale(const sf::Vector2f& scale)
{
    this->scale = scale;
    render.setSize(scale);
    collider->SetOwnerScale(scale);
    SetOrigin(originPreset);
}

void TriggerObject::SetRotation(float angle)
{
    rotation = angle;
    render.setRotation(angle);
    collider->SetRotation(angle);
}

void TriggerObject::SetPosition(const sf::Vector2f& pos)
{
    position = pos;
    render.setPosition(position);
    collider->SetPosition(position);
}

void TriggerObject::SetOrigin(Origins preset)
{
    originPreset = preset;
    origin = Utils::SetOrigin(render, preset);
    collider->SetOrigin(preset);
}

void TriggerObject::SetOrigin(const sf::Vector2f& newOrigin)
{
    originPreset = Origins::Custom;
    origin = newOrigin;
    render.setOrigin(origin);
    collider->SetOrigin(newOrigin);
}

void TriggerObject::Start()
{
    SetScale(scale);
    SetPosition(position);
    SetRotation(rotation);
    SetOrigin(originPreset);
    collider->Reset();
}

void TriggerObject::Render(sf::RenderWindow& renderWindow)
{
    collider->Render(renderWindow);
}

void TriggerObject::OnCollisionEnter(Collider* target)
{
    if (target->GetColliderLayer() == ColliderLayer::Player)
    {
        for (auto& enterEvent : triggerEvents)
        {
            if (enterEvent)
                enterEvent();
        }
        SetDestory(true);
    }
}

sf::FloatRect TriggerObject::GetLocalBounds() const
{
    return sf::FloatRect();
}

sf::FloatRect TriggerObject::GetGlobalBounds() const
{
    return sf::FloatRect();
}