#include "stdafx.h"
#include "GameManager.h"
#include "Player.h"
#include "Camera.h"
#include "UITextGameObject.h"
#include "BackgroundColorBox.h"

GameManager::GameManager()
	: isRestart(false)
	, currentTimer(400.f)
	, currentScore(0)
	, life(3)
	, restartPath("temporaryStorage.json")
	, isPlayerDead(false)
	, worldName("1-1")
	, currentCoinCount(0)
	, scoreUI(nullptr)
	, coinUI(nullptr)
	, timerUI(nullptr)
	, scoreString("000000")
	, highscore(0)
	, isStartClearEvent(false)
	, currentEventTime(0.f)
	, clearEvnetScoreUpTime(0.02f)
	, waitTime(1.f)
	, isEndAdjustment(false)
	, isGameOver(false)
	, marioHP(1)
	, isPlaying(false)
	, isGameClear(false)
	, currentGameOverCreditTime(0.f)
	, isGameOverCredit(false)
{
	  
}


void GameManager::Update(float dt)
{
	if (isGameOverCredit)
	{
		currentGameOverCreditTime += TimeManager::GetInstance().GetUnScaleDeletaTime();

		if (currentGameOverCreditTime > 5.f)
		{
			currentGameOverCreditTime = 0.f;
			SceneManager::GetInstance().ChangeScene(SceneIds::TitleScene);
		}
		return;
	}


	if (!isGameClear)
	{
		currentTimer -= dt;
		timerUI->SetString(std::to_string((int)currentTimer));
	}

	if (isPlaying &&  !isPlayerDead && !isGameClear && currentTimer <= 0.f)
	{
		Player* player = (Player*)SceneManager::GetInstance().GetCurrentScene()->GetObjectVector(LayerType::Player)[0];
		player->GetFSM().ChangeState(PlayerStateType::Dead);
		isPlayerDead = true;
	}

	if (isStartClearEvent)
	{
		currentEventTime += dt;
		if ((int)currentTimer == 0)
		{
			countDown.stop();
			if (currentEventTime > waitTime)
			{
				isEndAdjustment = true;
				isPlaying = false;
				// SceneManager::GetInstance().ChangeScene(SceneIds::SceneDev1);
				currentTimer = 0.f;
			}
		}
		else
			OnClearAdjustment();
	}
}


void GameManager::Reset()
{
	life = 3;
	isPlayerDead = false;
	currentCoinCount = 0;
	currentScore = 0;
	isStartClearEvent = false;
	isEndAdjustment = false;
	isGameOver = false;
	isPlaying = false;
	currentGameOverCreditTime = 0.f;
	isGameOverCredit = false;
	currentTimer = 400.f;
}

void GameManager::OnClearAdjustment()
{
	if (currentEventTime > clearEvnetScoreUpTime)
	{
		currentTimer -= 1.f;
		currentEventTime = 0.f;
		AddScore(100);

		if (currentTimer < 100)
		{
			if (currentTimer < 10)
				timerUI->SetString("00" + std::to_string((int)currentTimer));
			else
				timerUI->SetString("0" + std::to_string((int)currentTimer));
		}
		else
			timerUI->SetString(std::to_string((int)currentTimer));
	}
}

void GameManager::OnRestart()
{
	--life;
	currentTimer = 400.f;
	isPlaying = true;
	isRestart = true;
}

void GameManager::OnSavePoint(const sf::Vector2f& restartPos)
{
	restartPosition = restartPos;
	SceneManager::GetInstance().GetCurrentScene()->Save(restartPath);
}

void GameManager::SetGameClear()
{
	isGameClear = true;
}

void GameManager::OnGameClearEvent()
{
	isStartClearEvent = true;
	currentTimer = (float)((int)currentTimer);
	countDown.setVolume(SoundManger::GetInstance().GetSfxVolum());
	countDown.setBuffer(ResourcesManager<sf::SoundBuffer>::GetInstance().Get("CountDown"));
	countDown.setLoop(false);
	countDown.play(); 
}

void GameManager::GameStartInit()
{
	if (currentCoinCount < 10)
		coinString = "0" + std::to_string(currentCoinCount);
	else
		coinString = std::to_string(currentCoinCount);

	std::string score = std::to_string(currentScore);
	int size = (int)score.size() - 1;
	for (int i = 5; i > 0 ; --i)
	{
		scoreString[i] = score[size--];
		if (size < 0)
			break;
	}

	coinUI->SetString(coinString);

	if (currentTimer < 100)
	{
		if(currentTimer < 10)
			timerUI->SetString("00" + std::to_string((int)currentTimer));
		else
			timerUI->SetString("0" + std::to_string((int)currentTimer));
	}
	else
		timerUI->SetString(std::to_string((int)currentTimer));
	scoreUI->SetString(scoreString);
}

void GameManager::NextStage()
{
	isPlaying = false;
	InputManager::GetInstance().SetInputable(false);
	SceneIds currentId = SceneManager::GetInstance().GetCurrentSceneId();
	if (currentId == SceneIds::SceneDev1)
	{
		Player* player = (Player*)SceneManager::GetInstance().GetCurrentScene()->GetObjectVector(LayerType::Player)[0];
		marioHP = player->GetCurrentHP();
		SceneManager::GetInstance().ChangeScene(SceneIds::Stage2);
		player = (Player*)SceneManager::GetInstance().GetCurrentScene()->GetObjectVector(LayerType::Player)[0];
		player->ChangeMario(marioHP);

		isPlaying = true;
		currentTimer = 400.f;
	}
	else if (currentId == SceneIds::Stage2)
	{
		SceneManager::GetInstance().ChangeScene(SceneIds::TitleScene);
	}
	isEndAdjustment = false;
	isGameClear = false;
	isStartClearEvent = false;
}

void GameManager::ReStart()
{	
	if (life == 0)
	{
		Scene* scene = SceneManager::GetInstance().GetCurrentScene();
		BackgroundColorBox* background = scene->AddGameObject(new BackgroundColorBox(), LayerType::UI);
		background->SetScale({ 2000.f, 1300.f });
		background->SetColor(sf::Color::Black);
		background->Start();

		background->sortingOrder = -1;
		UITextGameObject* creadit = scene->AddGameObject(new UITextGameObject("DungGeunMo", "Ending", 80), LayerType::UI);
		creadit->sortingOrder = -2;
		creadit->SetPosition({ 960.f, 500.f });
		creadit->SetOrigin(Origins::MiddleCenter);
		creadit->SetString("GAME OVER!");
		creadit->Start();

		SoundManger::GetInstance().PlayBgm("GameOver", false);
		// SceneManager::GetInstance().ChangeScene(SceneIds::TitleScene);
		isRestart = false;
		isGameOver = true;
		isGameOverCredit = true;
	}
	else
	{
		isPlayerDead = false;
		SceneManager::GetInstance().ChangeScene(SceneManager::GetInstance().GetCurrentSceneId());
		SceneManager::GetInstance().GetCurrentScene()->Load(restartPath);
		isRestart = false;

		Player* player = (Player*)SceneManager::GetInstance().GetCurrentScene()->GetObjectVector(LayerType::Player)[0];
		player->SetPosition(restartPosition);
		player->ChangeSmallMario();
		SceneManager::GetInstance().GetCurrentScene()->GetMainCamera()->SetCameraPosition(restartPosition);
	}
}

void GameManager::PlayerDie()
{
	if(isPlayerDead)
		return;
	isPlayerDead = true;
	OnRestart();
}

void GameManager::HaveCoin()
{
	++currentCoinCount;
	currentScore += 200;

	if (currentCoinCount >= 100)
	{
		++life;
		currentCoinCount -= 100;

		SoundManger::GetInstance().PlaySfx("OneUp");
	}

	if (currentCoinCount < 10)
		coinString = "0" + std::to_string(currentCoinCount);
	else
		coinString = std::to_string(currentCoinCount);

	std::string score = std::to_string(currentScore);
	int size = (int)score.size() - 1;
	for (int i = 5; i > 0; --i)
	{
		scoreString[i] = score[size--];
		if (size < 0)
			break;
	}

	coinUI->SetString(coinString);
	scoreUI->SetString(scoreString);

}

void GameManager::OnLifeUp()
{
	++life;
}

void GameManager::AddScore(int score)
{
	currentScore += score;

	std::string strScore = std::to_string(currentScore);
	int size = (int)strScore.size() - 1;
	for (int i = 5; i > 0; --i)
	{
		scoreString[i] = strScore[size--];
		if (size < 0)
			break;
	}

	scoreUI->SetString(scoreString);
}
