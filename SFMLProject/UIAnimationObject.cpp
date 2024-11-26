#include "stdafx.h"
#include "UIAnimationObject.h"
#include "Animator.h"
#include "Animation.h"

UIAnimationObject::UIAnimationObject(const std::string& name)
    : UIGameObject(name)
{
    CreateAnimator();
}

void UIAnimationObject::SetPosition(const sf::Vector2f& pos)
{
    position = pos;
    sprite.setPosition(pos);
}

void UIAnimationObject::SetScale(const sf::Vector2f& scale)
{
    this->scale = scale;
    animator->SetScale(scale);
}
void UIAnimationObject::SetOrigin(Origins preset)
{
    originPreset = preset;
    origin = Utils::SetOrigin(sprite, preset);
}

void UIAnimationObject::SetOrigin(const sf::Vector2f& newOrigin)
{
    originPreset = Origins::Custom;
    origin = newOrigin;
    sprite.setOrigin(origin);
}

void UIAnimationObject::CreateAnimator()
{
    if (animator != nullptr)
        return;

    animator = new Animator(this, sprite);
}

void UIAnimationObject::Start()
{
    SetScale(scale);
    SetPosition(position);
    SetRotation(rotation);

    SetOrigin(originPreset);
    animator->Start();
}

void UIAnimationObject::Update(const float& deltaTime)
{
    animator->Update(deltaTime);
}

void UIAnimationObject::Render(sf::RenderWindow& renderWindow)
{
    animator->Render(renderWindow);
}

sf::FloatRect UIAnimationObject::GetLocalBounds() const
{
    return sprite.getLocalBounds();
}

sf::FloatRect UIAnimationObject::GetGlobalBounds() const
{
    return sprite.getGlobalBounds();
}