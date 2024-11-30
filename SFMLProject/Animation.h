#pragma once

class Animator;

struct AnimationInfo
{
	std::string		textureID;
	sf::IntRect		uvRect;
	sf::Vector2u	rectSize;
	float			duration;

	std::vector<std::function<void()>> startEvents;
	std::vector<std::function<void()>> endEvents;

	AnimationInfo() {}
	AnimationInfo(const std::string& texID, const sf::Vector2u& rectSize, const sf::IntRect& uvRect, float duration)
		: textureID(texID)
		, rectSize(rectSize)
		, uvRect(uvRect)
		, duration(duration) {}
};

class Animation
{
protected:
	Animator*					animator;
	std::vector<AnimationInfo>	frameInfoVector;
	const sf::Texture*			texture;

	std::string					textureID;
	std::string					animationID;

	unsigned int				frameCount;
	unsigned int				currentIndex;
	float						totalFrameTime;
	float						currentAnimationTime;
	float						animationSpeed;

	bool						isUnscale;
	bool						isPlaying;
	bool						isRepeat;

public:
	void Play(float speed, bool isRepeat = false, unsigned int index = 0);
	void Stop();
	void Reset();

	void Update(float deltaTime);

public:
	void AddAnimationInfo(const AnimationInfo& animationInfo, unsigned int index);
	void AddAnimationInfo(const AnimationInfo& animationInfo);

	void CreateAnimationInfo(const sf::Texture* texture, const std::string& textureID, const sf::Vector2u& rectSize, int frameCount, float frameTime, bool isRepeat = false);
	void CreateAnimationInfo(const sf::Texture* texture, const std::string& textureID, const std::string& animationName, const std::vector<AnimationInfo>& frames);
	void SetAnimationInfo(const AnimationInfo& animationInfo, unsigned int index);
	void SetRectSize(sf::Vector2u rectSize, unsigned int index);
	void SetRepeat(bool repeat) { isRepeat = repeat; }
	void SetUnScaleUpdate(bool unscale) { isUnscale = unscale; }


	void SetAnimationStartEvent(std::function<void()>  event, unsigned int index);
	void SetAnimationEndEvent(std::function<void()>  event, unsigned int index);
	void SetAnimationName(const std::string name) { animationID = name; }
	void ClearStartEvent(unsigned int index);
	void ClearEndEvent(unsigned int index);
	void SetAnimator(Animator* animator) { this->animator = animator; }
	const sf::Texture* GetTexture() const { return texture; }
	const sf::Vector2u& GetUvRect() { return frameInfoVector[0].rectSize; }
	const sf::Vector2u& GetUvRect(int index) { return frameInfoVector[index].rectSize; }

	const std::string& GetAnimationName() { return animationID; }
	const std::string& GetTextureID() { return textureID; }
	const std::vector<AnimationInfo>& GetFrameInfo() { return frameInfoVector; }

	int GetFrameCount() { return frameCount; }
	int GetCurrentIndex() { return currentIndex; }
	bool IsRepeat() { return isRepeat; }
	bool IsUnScale() { return isUnscale; }
public:
	bool SaveCSV(const std::string& filePath);
	bool loadFromFile(const std::string& filePath);

public:
	Animation();
	Animation(const sf::Texture* texture, const std::string& textureID, const std::string& animationName, const sf::Vector2u& rectSize, int frameCount ,float frameTime, bool isRepeat = false);
	Animation(const Animation& other);
	Animation(const std::string& filePath);
	virtual ~Animation();
};

