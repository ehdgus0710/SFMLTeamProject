#include "stdafx.h"
#include "BackgroundSprite.h"
#include "Camera.h"

BackgroundSprite::BackgroundSprite(const std::string& texId, const std::string& name)
	: SpriteGameObject(texId, name)
	, followTarget(nullptr)
	, followCamera(nullptr)
	, useTargetFollow(false)
	, useCameraFollow(false)
{
}

void BackgroundSprite::Update(const float& deltaTime)
{
	if (useCameraFollow)
	{
		SetPosition(followCamera->GetCameraPosition());
	}
	else if (useTargetFollow)
	{
		SetPosition(followTarget->GetPosition());
	}
}