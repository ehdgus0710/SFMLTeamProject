#pragma once

class Player;
class UITextGameObject;

class GameManager : public Singleton<GameManager>
{
	friend Singleton<GameManager>;
private:
public:
	void GameStartInit();

public:
	void Update(float dt);

protected:
	GameManager();
	virtual ~GameManager() = default;
	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;
};

