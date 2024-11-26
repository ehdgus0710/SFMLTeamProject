#include "stdafx.h"
#include "InGameUIHub.h"
#include "Scene.h"
#include "GameManager.h"
#include "UITextGameObject.h"
#include "UICoinObject.h"

InGameUIHub::InGameUIHub(const std::string& textId, const std::string& name)
    : GameObject(name)
    , fontId(textId)
    , scoreNameUI(nullptr)
    , worldNameUI(nullptr)
    , timeNameUI(nullptr)
    , marioNameUI(nullptr)
    , scoreUI(nullptr)
    , worldUI(nullptr)
    , timerUI(nullptr)
    , coinUI(nullptr)
{
}
void InGameUIHub::PushBackObject()
{
    uiTextGameObjectMaps.insert({ worldNameUI->GetName(), worldNameUI});
    uiTextGameObjectMaps.insert({timeNameUI->GetName(), timeNameUI});
    uiTextGameObjectMaps.insert({marioNameUI->GetName(), marioNameUI});
    uiTextGameObjectMaps.insert({worldUI->GetName(), worldUI});
    uiTextGameObjectMaps.insert({scoreUI->GetName(), scoreUI});
    uiTextGameObjectMaps.insert({timerUI->GetName(), timerUI});
    uiTextGameObjectMaps.insert({ coinUI->GetName(), coinUI });

}
void InGameUIHub::Start()
{
    GameObject::Start();

    Scene* currentScene = SceneManager::GetInstance().GetCurrentScene();
    // scoreNameUI = currentScene->AddGameObject(new UITextGameObject(fontId, "ScoreUI", 100), LayerType::UI);
    worldNameUI = currentScene->AddGameObject(new UITextGameObject(fontId, "WorldNameUI", 70), LayerType::UI);
    timeNameUI = currentScene->AddGameObject(new UITextGameObject(fontId, "TimeUI", 70), LayerType::UI);
    marioNameUI = currentScene->AddGameObject(new UITextGameObject(fontId, "Mario", 70), LayerType::UI);
    // coinUI = currentScene->AddGameObject(new UITextGameObject(fontId, "CoinUI", 100), LayerType::UI);

    worldUI = currentScene->AddGameObject(new UITextGameObject(fontId, "WorldUI", 70), LayerType::UI);
    scoreUI = currentScene->AddGameObject(new UITextGameObject(fontId, "ScoreUI", 70), LayerType::UI);
    timerUI = currentScene->AddGameObject(new UITextGameObject(fontId, "TimerUI", 70), LayerType::UI);
    coinUI = currentScene->AddGameObject(new UITextGameObject(fontId, "CoinUI", 70), LayerType::UI);

    coinAnimationUI = currentScene->AddGameObject(new UICoinObject("CoinAnimationUI"), LayerType::UI);

    PushBackObject();

    worldNameUI->SetString("WORLD");
    timeNameUI->SetString("TIME");
    marioNameUI->SetString("MARIO");

    worldNameUI->SetPosition({ 1250.f, 50.f });
    timeNameUI->SetPosition({ 1700.f, 50.f });
    marioNameUI->SetPosition({ 100.f, 50.f });

    worldUI->SetPosition({ 1200.f, 85.f });
    scoreUI->SetPosition({ 100.f, 80.f });
    timerUI->SetPosition({ 1660.f, 85.f });
    
    coinUI->SetPosition({ 770.f, 55.f });
    coinAnimationUI->SetPosition({ 700.f, 100.f });

    worldNameUI->SetOrigin(Origins::MiddleCenter);
    timeNameUI->SetOrigin(Origins::MiddleCenter);
    marioNameUI->SetOrigin(Origins::MiddleLeft);
    worldUI->SetOrigin(Origins::MiddleCenter);

    scoreUI->SetOrigin(Origins::MiddleRight);
    timerUI->SetOrigin(Origins::MiddleRight);
    coinUI->SetOrigin(Origins::MiddleLeft);

    worldUI->Start();
    scoreUI->Start();
    timerUI->Start();
    coinUI ->Start();
    worldNameUI->Start();
    timeNameUI->Start();
    marioNameUI->Start();
    coinAnimationUI->Start();
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
