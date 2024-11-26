#include "stdafx.h"
#include "UICoinObject.h"
#include "Animator.h"

UICoinObject::UICoinObject(const std::string& name)
	: UIAnimationObject(name)
{
	animator->LoadCsv("animators/coin.csv");
}

void UICoinObject::Start()
{
	UIAnimationObject::Start();

	subSprite.setTexture(ResourcesManager<sf::Texture>::GetInstance().Get("font"));
	subSprite.setTextureRect({ 64,40,7,7 });
	subSprite.scale(sf::Vector2f::one * 4);
	Utils::SetOrigin(subSprite, Origins::MiddleCenter);
	sf::Vector2f pos = position + sf::Vector2f::right * 43.f;
	pos.y += 5.f;
	subSprite.setPosition(pos);

	animator->ChangeAnimation("coinIdle", true);
}

void UICoinObject::Render(sf::RenderWindow& renderWindow)
{
	animator->Render(renderWindow);
	renderWindow.draw(subSprite);
}
