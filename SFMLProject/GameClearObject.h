
#pragma once
#include "GameObject.h"
#include "GameObjectSaveData.h"

class Player;

class GameClearObject : public GameObject
{
protected:
	sf::Sprite		flagSprite;

	std::vector<std::function<void()>> gameClearEvents;

	sf::RectangleShape	render;
	Player*				player;

	sf::Vector2f		maxStartPosition;
	sf::Vector2f		startPosition;
	sf::Vector2f		destinationPosition;
	sf::Vector2f		endMovePosition;

	sf::Vector2f		flagStartPosition;
	sf::Vector2f		flagEndPosition;

	float				currentFlagMoveTime;
	float				flagMoveTime;
	float				currentTime;
	float				endMoveTime;
	float				currentEndMoveTime;
	float				moveTime;
	int					currentEventIndex;
	int					eventCount;
	bool				isStartClearEvent;
	bool				isStartFlip;
	bool				isStartMove;
	
public:
	void SetScale(const sf::Vector2f& scale) override;
	void SetRotation(float angle) override;
	void SetPosition(const sf::Vector2f& pos) override;
	
	void SetMaxStartPosition(const sf::Vector2f& pos) { maxStartPosition = pos; }
	void SetDestinationPosition(const sf::Vector2f& pos) { destinationPosition = pos; }
	void SetEndMovePosition(const sf::Vector2f& pos) { endMovePosition = pos; }

	sf::Vector2f GetMaxStartPosition() { return maxStartPosition; }
	sf::Vector2f GetDestinationPosition() { return destinationPosition; }
	sf::Vector2f GetEndMovePosition() { return endMovePosition; }

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void StartMove();
	void FlipEvent();
	void PlayerCastleMove();
public:
	void Start() override;

	void Update(const float& deltaTime) override;
	void Render(sf::RenderWindow& renderWindow) override;

	void OnCollisionEnter(Collider* target) override;

	sf::FloatRect GetLocalBounds() const;
	sf::FloatRect GetGlobalBounds() const;
public:
	GameClearSaveData GetGameClearSaveData() const;
	void LoadGameClearSaveData(const GameClearSaveData& data);

public:
	GameClearObject(const std::string& name = "GameClearPoint");
	virtual ~GameClearObject() = default;
	GameClearObject& operator= (const GameClearObject& other) = delete;
};

