#pragma once

class Animation;

class Animator : public Entity
{
protected:
	std::unordered_map<std::string, Animation*> animationMap;
	Animation*									currentAnimation;
	sf::Sprite*									sprite;
	sf::IntRect									uvRect;

	sf::Vector2f								rectSize;
	sf::Vector2f								scale;

	GameObject*									owner;

	float										animationSpeed;
	bool										isPlaying;

protected:
	void StartAnimation(Animation* animation, bool isRepeat = false);

public:
	Animation* GetAnimation(const std::string& animationName);
	Animation* GetCurrentAnimation() { return currentAnimation; }

	void CreateAnimation(const std::string& id, const std::string& animationName, const sf::Vector2u& rectSize, int frameCount, float frameTime, bool isRepeat = false);
	void CreateAnimation(const sf::Texture* texture, const std::string& id, const std::string& animationName, const sf::Vector2u& rectSize, int frameCount, float frameTime, bool isRepeat = false);
	void AddAnimation(Animation* animation, const std::string& animationName);

	void ChangeAnimation(const std::string& animationName,bool isRepeat = false, bool isUnscale = false, unsigned int index = 0);
	void Render(sf::RenderWindow& renderWindow);
	void SetCurrentFrameRect(const sf::IntRect& rect);
	void SetCurrentFrameInfo(const sf::Vector2u& size, const sf::IntRect& rect);
	sf::Sprite& GetCurrentSprite() { return *sprite; }

	void SetAnimationSpeed(float speed);

	void SetOrigin(Origins preset);
	void SetOrigin(const sf::Vector2f& newOrigin);

	void SetScale(const sf::Vector2f& scale);
	sf::Vector2f GetScale() { return rectSize;	}

	void SetPlaying(bool isPlay) { isPlaying = isPlay; }
	void SetPlaying(Animation* animation, bool isPlay);
	bool IsPlaying() { return isPlaying; }

	sf::FloatRect GetLocalBounds() const;
	sf::FloatRect GetGlobalBounds() const;

	void Play(bool isRepeat = false, bool isUnscale = false);

	std::unordered_map<std::string, Animation*> GetMap() { return animationMap; }
public:
	void Update(const float& deltaTime) override;
	void Start() override;
	bool Save() const override;
	bool Load() override;
	bool SaveCsv(const std::string& filePath) const override;
	bool LoadCsv(const std::string& filePath) override;


public:
	Animator(GameObject* owner, sf::Sprite& sprite);
	Animator(const Animator& other);
	~Animator();
};

