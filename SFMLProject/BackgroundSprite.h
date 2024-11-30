#pragma once
#include "SpriteGameObject.h"

class Camera;

class BackgroundSprite : public SpriteGameObject
{
protected:
	Camera*			followCamera;
	GameObject*		followTarget;

	bool			useCameraFollow;
	bool			useTargetFollow;
public:
	void SetTargetFollow(GameObject* target) { followTarget = target; useTargetFollow = true; useCameraFollow = false; }
	void SetCameraFollow(Camera* target) { followCamera = target; useTargetFollow = false; useCameraFollow = true; }

public:
	void Update(const float& deltaTime) override;
public:
	BackgroundSprite(const std::string& texId, const std::string& name = "");
	virtual ~BackgroundSprite() = default;
	BackgroundSprite& operator= (const BackgroundSprite& other) = delete;
};

