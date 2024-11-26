#pragma once
class StartUIObject : public GameObject
{
private:
	sf::RectangleShape	blockRect;
	sf::Sprite			marioSprite;
	sf::Text			worldNameText;
	sf::Text			lifeText;
	sf::Sprite			subSprite;

	float				currentLifeTime;
	float				lifeTime;

public:
	void Start() override;
	void Update(const float& deltaTime) override;
	void Render(sf::RenderWindow& renderWindow) override;

	sf::FloatRect GetLocalBounds() const;
	sf::FloatRect GetGlobalBounds() const;
public:
	StartUIObject();
	~StartUIObject();
};

