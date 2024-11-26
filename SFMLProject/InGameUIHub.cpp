#include "stdafx.h"
#include "InGameUIHub.h"
#include "Scene.h"
#include "GameManager.h"
#include "UITextGameObject.h"

InGameUIHub::InGameUIHub(const std::string& textId, const std::string& name)
    : GameObject(name)
{
}
void InGameUIHub::PushBackObject()
{

}
void InGameUIHub::Start()
{
    GameObject::Start();
}

void InGameUIHub::OnAllDisable()
{
    for (auto& object : uiTextGameObjectMaps)
    {
        object.second->SetActive(false);
    }
    
}

void InGameUIHub::OnAllActive()
{
    for (auto& object : uiTextGameObjectMaps)
    {
        object.second->SetActive(true);
    }
}

UITextGameObject* InGameUIHub::GetTextGameObject(const std::string& name)
{
    auto iter = uiTextGameObjectMaps.find(name);
    if (iter != uiTextGameObjectMaps.end())
    {
        return iter->second;
    }

    return nullptr;
}

sf::FloatRect InGameUIHub::GetLocalBounds() const
{
    return sf::FloatRect();
}

sf::FloatRect InGameUIHub::GetGlobalBounds() const
{
    return sf::FloatRect();
}
