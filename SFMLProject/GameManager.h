#pragma once

class Player;
class UITextGameObject;

class GameManager : public Singleton<GameManager>
{
	friend Singleton<GameManager>;
private:
	sf::Vector2f	playerReStartPosition;


	bool			isStart;
	bool			isPlaying;
	bool			isRestart;
	bool			isChangeScene;
public:
	void Reset();
	void GameStartInit();
	void PlayerDead();
	void OnChangeScene();
	bool IsChangeScene() { return isChangeScene; }

	sf::Vector2f GetRestartPosition() { return playerReStartPosition; }

	bool IsRestart() { return isRestart; }
public:
	void Update(float dt);

protected:
	GameManager();
	virtual ~GameManager() = default;
	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;
};

