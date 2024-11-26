#include "stdafx.h"
#include "BackgroundColorBox.h"
#include "Camera.h"


BackgroundColorBox::BackgroundColorBox(const std::string& name)
    : GameObject(name)
    , mainCamera(nullptr)
{
}


void BackgroundColorBox::Start()
{
	SetScale(scale);
	SetPosition(position);
	SetRotation(rotation);
	SetOrigin(originPreset);

	render.setFillColor(color);

	mainCamera = SceneManager::GetInstance().GetCurrentScene()->GetMainCamera();
}

void BackgroundColorBox::Update(const float& deltaTime)
{
	SetPosition(mainCamera->GetCameraPosition());
}


void BackgroundColorBox::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;
	render.setScale(scale);
	render.setSize(scale);
	SetOrigin(originPreset);
}

void BackgroundColorBox::SetSize(const sf::Vector2f& size)
{
	rectSize = size;
	render.setSize(rectSize);
}

void BackgroundColorBox::SetRotation(float angle)
{
	rotation = angle;
	render.setRotation(angle);
}

void BackgroundColorBox::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	render.setPosition(position);
}

void BackgroundColorBox::SetOrigin(Origins preset)
{
	originPreset = preset;
	origin = Utils::SetOrigin(render, preset);
}

void BackgroundColorBox::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	render.setOrigin(origin);
}

void BackgroundColorBox::Render(sf::RenderWindow& renderWindow)
{
    renderWindow.draw(render);
}

sf::FloatRect BackgroundColorBox::GetLocalBounds() const
{
    return render.getLocalBounds();
}

sf::FloatRect BackgroundColorBox::GetGlobalBounds() const
{
    return render.getGlobalBounds();
}
