#pragma once
#include "GameObject.h"

class Camera;

class BackgroundColorBox : public GameObject
{
protected:
	sf::RectangleShape	render;
	sf::Vector2f		rectSize;
	sf::Color			color;
	Camera*				mainCamera;

public:

	void SetScale(const sf::Vector2f& scale) override;
	void SetRotation(float angle) override;
	void SetPosition(const sf::Vector2f& pos) override;
	void SetColor(const sf::Color& color) { this->color = color; }

	void SetSize(const sf::Vector2f& size);

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

public:
	void Start() override;
	void Update(const float& deltaTime) override;
	void Render(sf::RenderWindow& renderWindow) override;

	sf::FloatRect GetLocalBounds() const;
	sf::FloatRect GetGlobalBounds() const;
public:
	bool Save() const override { return false; }
	bool Load() override { return false; }
	bool SaveCsv(const std::string& filePath) const { return false; }
	bool LoadCsv(const std::string& filePath) { return false; }

public:
	BackgroundColorBox(const std::string& name = "Background");
	virtual ~BackgroundColorBox() = default;
	BackgroundColorBox& operator= (const BackgroundColorBox& other) = delete;
};

