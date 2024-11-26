#pragma once

class Player;
class UITextGameObject;

class GameManager : public Singleton<GameManager>
{
	friend Singleton<GameManager>;
private:
	UITextGameObject* coinUI;
	UITextGameObject* timerUI;
	UITextGameObject* scoreUI;

	std::string		restartPath;
	std::string		worldName;
	sf::Vector2f	restartPosition;

	std::string		coinString;
	std::string		scoreString;

	float			currentTimer;
	float			clearEvnetScoreUpTime;
	float			currentEventTime;
	float			waitTime;

	float			currentGameOverCreditTime;
	unsigned int	currentCoinCount;
	unsigned int	currentScore;
	int				life;
	int				highscore;
	int				marioHP;

	bool			isRestart;
	bool			isPlayerDead;
	bool			isGameClear;
	bool			isStartClearEvent;
	bool			isEndAdjustment;
	bool			isPlaying;
	bool			isGameOver;
	bool			isGameOverCredit;
	sf::Sound		countDown;
public:

	bool IsGameOver() { return isGameOver; }
	bool IsGameClear() { return isGameClear; }
	bool IsRestart() { return isRestart; }
	bool IsEndAdjustment() { return isEndAdjustment; }
	bool IsGamePlaying() { return isPlaying; }
	bool IsGameOverCredit() { return isGameOverCredit; }
	void Reset();

	void OnClearAdjustment();
	void SetEndAdjustment(bool isEnd) { isEndAdjustment = isEnd; }
	void OnRestart();
	void OnSavePoint(const sf::Vector2f& restartPos);
	void SetGameClear();
	void OnGameClearEvent();
	void SetHighScore(int score) { highscore = score; }

	void GameStartInit();

	void NextStage();
	void ReStart();
	void PlayerDie();
	void HaveCoin();
	void OnLifeUp();
	void AddScore(int score);

	const std::string& GetWorldName() { return worldName; }
	void SetWorldName(const std::string& name) { worldName = name; }
	

	void SetTimerUI(UITextGameObject* ui) { timerUI = ui; }
	void SetCoinUI(UITextGameObject* ui) { coinUI = ui; }
	void SetScoreUI(UITextGameObject* ui) { scoreUI = ui; }

	void SetMarioHp(int hp) { marioHP = hp; }
	int GetCurrentLife() { return life; }
	int GetMarioHp() { return marioHP; }

public:
	void Update(float dt);

protected:
	GameManager();
	virtual ~GameManager() = default;
	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;
};

