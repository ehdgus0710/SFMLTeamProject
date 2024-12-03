#include "stdafx.h"
#include "SkillCoolTimeUI.h"

SkillCoolTimeUI::SkillCoolTimeUI(const std::string& texId, const std::string& name)
	: UISpriteGameObject(texId, name)
	, currentTime(0.f)
	, coolTime(3.f)
	, isCoolTimeCheck(false)
{
}


void SkillCoolTimeUI::OnSkillCoolTime()
{
	isCoolTimeCheck = true;
	currentTime = 0.f;
}

void SkillCoolTimeUI::SetSkillCooltime(float currentTime, float coolTime)
{
	this->currentTime = currentTime;
	this->coolTime = coolTime;

	sf::Vector2f iconsize = drawnicon.getLocalBounds().getSize();
	float radius = (iconsize.x + iconsize.y) * 2.f;
	int vac = (int)mask.getVertexCount();
	float ratio = Utils::Clamp(currentTime / coolTime, 0.f, 1.f);

	for (int i = 1; i < vac; ++i)
	{
		float angle = ((i - 4) / 3.f * 2.f * (1 - ratio) - 0.5f) * Utils::PI;
		mask[i].position = { radius * cosf(angle),radius * sinf(angle) };
		mask[i].position += iconsize * 0.5f;
	}
	renderTexture.clear(sf::Color(0, 0, 0, 0));

	renderTexture.draw(drawnicon);
	if (ratio < 1.f)
	{
		maskRenderState.blendMode = sf::BlendMode(sf::BlendMode::One, sf::BlendMode::One, sf::BlendMode::ReverseSubtract);
		renderTexture.draw(mask, maskRenderState);
	}
	renderTexture.display();
	sprite.setTexture(renderTexture.getTexture(), true);
	SetOrigin(originPreset);
}

void SkillCoolTimeUI::OnSkillCheck()
{
	if (isCoolTimeCheck)
	{
		// currentTime += deltaTime;
		sf::Vector2f iconsize = drawnicon.getLocalBounds().getSize();
		float radius = (iconsize.x + iconsize.y) * 2.f;
		int vac = (int)mask.getVertexCount();
		float ratio = Utils::Clamp(currentTime / coolTime, 0.f, 1.f);

		for (int i = 1; i < vac; ++i)
		{
			float angle = ((i - 4) / 3.f * 2.f * (1 - ratio) - 0.5f) * Utils::PI;
			mask[i].position = { radius * cosf(angle),radius * sinf(angle) };
			mask[i].position += iconsize * 0.5f;
		}
		renderTexture.clear(sf::Color(0, 0, 0, 0));

		renderTexture.draw(drawnicon);
		if (ratio < 1.f)
		{
			maskRenderState.blendMode = sf::BlendMode(sf::BlendMode::One, sf::BlendMode::One, sf::BlendMode::ReverseSubtract);
			renderTexture.draw(mask, maskRenderState);
		}
		renderTexture.display();
		sprite.setTexture(renderTexture.getTexture(), true);
		sprite.setScale({ 2.f ,2.f });
		SetOrigin(originPreset);
	}
}

void SkillCoolTimeUI::Render(sf::RenderWindow& renderWindow)
{
	renderWindow.draw(sprite);
}

void SkillCoolTimeUI::Start()
{
	drawnicon.setTexture(ResourcesManager<sf::Texture>::GetInstance().Get(textureId));

	auto& tex = TEXTURE_MANAGER.Get(textureId);
	drawnicon.setTexture(tex);
	mask.setPrimitiveType(sf::PrimitiveType::TriangleFan);
	mask.resize(5);
	sf::Vector2f iconsize = drawnicon.getLocalBounds().getSize();
	float radius = (iconsize.x + iconsize.y) * 2.f;
	mask[0].position = iconsize * 0.5f;
	mask[0].color = sf::Color({ 90,90,90,0 });
	int vac = (int)mask.getVertexCount();
	for (int i = 1; i < vac; ++i)
	{
		float angle = ((i - 4 ) / 3.f * 2.f - 0.5f) * Utils::PI;
		mask[i].position = { radius * cosf(angle),radius * sinf(angle) };
		mask[i].position += iconsize * 0.5f;
		mask[i].color = sf::Color({ 90,90,90,0 });
	}
	renderTexture.create(tex.getSize().x, tex.getSize().y);

	SetScale(scale);
	SetPosition(position);
	SetRotation(rotation);
	SetOrigin(originPreset);
}