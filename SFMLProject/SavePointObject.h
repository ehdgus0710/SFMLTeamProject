#pragma once
#include "GameObject.h"
#include "GameObjectSaveData.h"

class SavePointObject : public GameObject
{
protected:
	sf::RectangleShape	render;
	sf::Vector2f		restartPosition;

public:
	void SetScale(const sf::Vector2f& scale) override;
	void SetRotation(float angle) override;
	void SetPosition(const sf::Vector2f& pos) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void SetRestartPosition(const sf::Vector2f& restartPos) { restartPosition = restartPos; }
	const sf::Vector2f GetRestartPosition() const { return restartPosition; }
public:
	void Start() override;
	void Render(sf::RenderWindow& renderWindow) override;

	void OnCollisionEnter(Collider* target) override;

	sf::FloatRect GetLocalBounds() const;
	sf::FloatRect GetGlobalBounds() const;
public:
	SavePointSaveData GetSavePointSaveData() const;
	void LoadSavePointSaveData(const SavePointSaveData& data);

public:
	SavePointObject(const std::string& name = "SavePoint");
	virtual ~SavePointObject() = default;
	SavePointObject& operator= (const SavePointObject& other) = delete;
};

