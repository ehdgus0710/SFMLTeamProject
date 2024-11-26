#include "stdafx.h"
#include "StartUIObject.h"
#include "GameManager.h"

void StartUIObject::Start()
{
    sortingOrder = 10;

    blockRect.setFillColor(sf::Color::Black);
    blockRect.setPosition({ 0.f, 0.f });
    blockRect.setSize({ 3000.f, 2000.f });

    marioSprite.setTexture(ResourcesManager<sf::Texture>::GetInstance().Get("mario_bros"));
    marioSprite.setTextureRect({ 176,32,16,16 });
    marioSprite.scale(sf::Vector2f::one * 4);
    
    sf::Vector2f resolutionSize = (sf::Vector2f)WindowManager::GetInstance().GetResolutionSize();

    Utils::SetOrigin(marioSprite, Origins::MiddleCenter);
    marioSprite.setPosition((resolutionSize  * 0.5f) - sf::Vector2f(100.f, 16.f));

    worldNameText.setFont(ResourcesManager<sf::Font>::GetInstance().Get("DungGeunMo"));
    worldNameText.setCharacterSize(50);
    worldNameText.setFillColor(sf::Color::White);
    worldNameText.setString("WORLD  " + GameManager::GetInstance().GetWorldName());
    Utils::SetOrigin(worldNameText, Origins::MiddleCenter);
    worldNameText.setPosition((resolutionSize * 0.5f) + sf::Vector2f(-50.f, -130.f));


    lifeText.setFont(ResourcesManager<sf::Font>::GetInstance().Get("DungGeunMo"));
    lifeText.setCharacterSize(50);
    lifeText.setPosition((resolutionSize * 0.5f) + sf::Vector2f(50.f, -40.f));
    lifeText.setString(std::to_string(GameManager::GetInstance().GetCurrentLife()));
    lifeText.setFillColor(sf::Color::White);

    TimeManager::GetInstance().SetTimeScale(0.f);
    
    subSprite.setTexture(ResourcesManager<sf::Texture>::GetInstance().Get("font"));
    subSprite.setTextureRect({ 64,40,7,7 });
    subSprite.scale(sf::Vector2f::one * 4);
    Utils::SetOrigin(subSprite, Origins::MiddleCenter);
    subSprite.setPosition(resolutionSize * 0.5f);
}

void StartUIObject::Update(const float& deltaTime)
{
    currentLifeTime += TimeManager::GetInstance().GetUnScaleDeletaTime();

    if (currentLifeTime >= lifeTime)
    {
        OnDestory();
        TimeManager::GetInstance().SetTimeScale(1.f);
        currentLifeTime = 0.f;
        SoundManger::GetInstance().PlayBgm(ResourcesManager<sf::SoundBuffer>::GetInstance().Get("MainTheme"));
    }
}

void StartUIObject::Render(sf::RenderWindow& renderWindow)
{
    renderWindow.draw(blockRect);
    renderWindow.draw(marioSprite);
    renderWindow.draw(worldNameText);
    renderWindow.draw(lifeText);
    renderWindow.draw(subSprite);

}

sf::FloatRect StartUIObject::GetLocalBounds() const
{
    return sf::FloatRect();
}

sf::FloatRect StartUIObject::GetGlobalBounds() const
{
    return sf::FloatRect();
}

StartUIObject::StartUIObject()
    : GameObject("StartUI")
    , currentLifeTime(0.f)
    , lifeTime(2.f)
{
}

StartUIObject::~StartUIObject()
{
}
