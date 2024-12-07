#pragma once

enum class MoveDirection
{
	LeftAndRight,
	UpAndDown,
	Random,
	end,
};

class Camera : public Entity
{
protected:
	sf::View		camera;
	sf::Vector2f	cameraPosition;
	sf::Vector2f	cameraSize;

	Rectangle		cameraBounds;
	Rectangle		cameraLimitRect;

	CameraType		type;
	GameObject*		followTarget;

	sf::Vector2f	followSpeed;
	float			speed;
	float			followTime;
	float			currentFollowTime;

	bool			isActive;
	bool			useFollowTarget;
	bool			useCameraLimit;
	bool			useLerpFollowTarget;


	sf::Vector2f	currentCameraShakePosition;
	sf::Vector2f	shakeRange;
	sf::Vector2f	shakeDirection;
	MoveDirection	moveType;
	float			shakeTime;
	float			currentShakeTime;
	float			shakePower;
	bool			useCameraShake;

private:
	void CameraLimit();
	void CameraShake(float deltaTime);

public:
	void SetActive(bool active) { isActive = active; }
	bool IsActive() { return isActive; }

	void SetCameraShake(const sf::Vector2f shakeRange, MoveDirection moveType, float shakePower,float shakeTime);

public:
	void SetViewInfo(const sf::View& view) { camera = view; }
	const sf::View& GetView() { return camera; }

	void SetCameraPosition(const sf::Vector2f& position);
	sf::Vector2f GetCameraPosition() { return cameraPosition; }

	const CameraType& GetCameraType() const { return type; }
	void SetFollowTarget(GameObject* traget, bool useLerpFollow = false) { followTarget = traget; useFollowTarget = true; useLerpFollowTarget = useLerpFollow; }

	void UseFollowTarget(bool isFollowTarget) { useFollowTarget = isFollowTarget; }

	void SetFollowTime(float time) { followTime = time; }
	float GetFollowTime() const { return followTime; }

	void SetCameraLimitRect(const Rectangle& rect, bool use = true);
	void UseCameraLimit(bool use) { useCameraLimit = true; }

	sf::FloatRect GetGlobalBounds();

	Rectangle GetCameraBound() { return cameraBounds; }
	float GetCameraLeftPosition() { return cameraPosition.x + cameraBounds.leftPosition; }

public:
	void Start() override;
	void Update(const float& deltaTime);
	virtual bool Save() const { return true; };
	virtual bool Load() { return true; };
	bool SaveCsv(const std::string& filePath) const override;
	bool LoadCsv(const std::string& filePath) override;
public:
	Camera(CameraType type);
	Camera(const sf::View& view, CameraType type);

	virtual ~Camera();
};

