#pragma once

class TimeManager : public Singleton<TimeManager>
{
	friend Singleton<TimeManager>;
private:
	sf::Clock		clock;
	sf::Time		sfTime;
	sf::Text		frameText;
	float			timeScale;

	float			time;
	float			realTime;

	float			deltaTime;
	float			realDeltatime;

	float			maximumAllowedTimestep;
	float			fixedDeltaTime;
	float			currentFixedTimestep;
	unsigned int	frameTarget;

	unsigned int	currentFrame;
	float			currentFrameTime;

public:
	bool IsFixedUpdate();

	void SetFixedTimeStep(float fixedTime) { fixedDeltaTime = fixedTime; }
	void SetMaximumAllowedTimestep(float timestep) { maximumAllowedTimestep = timestep; }

	float GetUnScaleDeletaTime() const { return realDeltatime; }
	float GetUnScaleFixedDeletaTime() const { return fixedDeltaTime; }
	float GetDeletaTime() const { return deltaTime * timeScale; }
	float GetFixedDeletaTime() const { return fixedDeltaTime * timeScale; }
	float GetTime() const 	{ return time; }
	float GetRealTime() const { return realTime; }
	float GetTimeScale() const { return timeScale; }
	sf::Time& GetTime() { return sfTime; }

	sf::Clock& GetClock() { return clock; }
	void SetTimeScale(float newTimeScale) { timeScale = newTimeScale; }

	void FrameCheck();
public:
	void Init();
	void Update();
	void Render(sf::RenderWindow& renderWindow);

protected:
	TimeManager();
	~TimeManager() override {}
	TimeManager(const TimeManager&) = delete;
	TimeManager& operator=(const TimeManager&) = delete;
};

