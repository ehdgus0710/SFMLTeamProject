#include "stdafx.h"
#include "Camera.h"

Camera::Camera(CameraType type)
	: type(type)
	, isActive(true)
	, followTarget(nullptr)
	, useCameraLimit(false)
	, useFollowTarget(false)
	, currentFollowTime(0.f)
	, followTime(0.f)
	, speed(0.f)
	, useLerpFollowTarget(false)
{
}

Camera::Camera(const sf::View& view, CameraType type)
	: type(type)
	, isActive(true)
	, followTarget(nullptr)
	, useCameraLimit(false)
	, useFollowTarget(false)
	, currentFollowTime(0.f)
	, followTime(0.f)
	, speed(0.f)
	, useLerpFollowTarget(false)
{
	camera = view;
	cameraPosition = camera.getCenter();
	cameraSize = camera.getSize();
	cameraBounds = Rectangle(cameraSize);
}

Camera::~Camera()
{
}

void Camera::CameraLimit()
{
 	auto size = camera.getSize() * 0.5f;


	cameraPosition.x = Utils::Clamp(cameraPosition.x , cameraLimitRect.leftPosition, cameraLimitRect.rightPosition);
	cameraPosition.y = Utils::Clamp(cameraPosition.y, cameraLimitRect.topPosition, cameraLimitRect.bottomPosition);

	if (cameraLimitRect.leftPosition > cameraLimitRect.rightPosition)
		cameraPosition.x = cameraLimitRect.rightPosition;

	camera.setCenter(cameraPosition);
}

void Camera::CameraShake(float deltaTime)
{
	currentShakeTime += deltaTime;

	if (currentShakeTime >= shakeTime)
	{
		currentCameraShakePosition = sf::Vector2f::zero;
		currentShakeTime = 0.f;
		useCameraShake = false;
		camera.setCenter(cameraPosition);
	}
	else
	{
		currentCameraShakePosition += shakeDirection * deltaTime * shakePower;

		if (shakeDirection.x < 0.f && currentCameraShakePosition.x <= -shakeRange.x)
		{
			shakeDirection.x = Utils::RandomRange(0.5f, 1.f);
		}
		else if (shakeDirection.x > 0.f && currentCameraShakePosition.x >= shakeRange.x)
		{
			shakeDirection.x = Utils::RandomRange(0.5f, 1.f) * -1.f;
		}

		if (shakeDirection.y < 0.f && currentCameraShakePosition.y <= -shakeRange.y)
		{
			shakeDirection.y = Utils::RandomRange(0.5f, 1.f);
		}
		else if (shakeDirection.y > 0.f && currentCameraShakePosition.y >= shakeRange.y)
		{
			shakeDirection.y = Utils::RandomRange(0.5f, 1.f) * -1.f;
		}
		camera.setCenter(cameraPosition + currentCameraShakePosition);
	}

}

void Camera::SetCameraShake(const sf::Vector2f shakeRange, MoveDirection moveType, float shakePower, float shakeTime)
{
	if (this->shakeTime - currentShakeTime > shakeTime || this->shakePower > shakePower)
		return;

	this->shakeRange = shakeRange;
	this->moveType = moveType;
	this->shakeTime = shakeTime;
	this->shakePower = shakePower;
	currentCameraShakePosition = sf::Vector2f::zero;
	currentShakeTime = 0.f;

	switch (moveType)
	{
	case MoveDirection::LeftAndRight:
		shakeDirection = sf::Vector2f(Utils::RandomRange(0.5f, 1.f), 0.f);
		break;
	case MoveDirection::UpAndDown:
		shakeDirection = sf::Vector2f(0.f, Utils::RandomRange(0.5f, 1.f));
		break;
	case MoveDirection::Random:
		shakeDirection = sf::Vector2f(Utils::RandomRange(0.5f, 1.f), Utils::RandomRange(0.5f, 1.f));
		break;
	case MoveDirection::end:
		break;
	default:
		break;
	}

	shakeDirection.Normalized();	
	useCameraShake = true;
}

void Camera::SetCameraPosition(const sf::Vector2f& position)
{
	cameraPosition = position; 
	camera.setCenter(cameraPosition);
}


void Camera::SetCameraLimitRect(const Rectangle& rect, bool use)
{
	cameraLimitRect = rect;


	cameraLimitRect.leftPosition -= cameraBounds.leftPosition;
	cameraLimitRect.rightPosition -= cameraBounds.rightPosition;
	cameraLimitRect.topPosition -= cameraBounds.topPosition;
	cameraLimitRect.bottomPosition -= cameraBounds.bottomPosition;

	useCameraLimit = use;
}

sf::FloatRect Camera::GetGlobalBounds()
{
	return { cameraPosition, camera.getSize() * 2.f };
}

void Camera::Start()
{
	// cameraBounds = sf::FloatRect(sf::Vector2f::zero, camera.getSize());
}

void Camera::Update(const float& deltaTime)
{
	if (useFollowTarget)
	{
		if (followTarget != nullptr)
		{
			if (useLerpFollowTarget)
			{
				cameraPosition = sf::Vector2f::SmoothDamp(cameraPosition, followTarget->GetPosition(), followSpeed, 0.5f, 1200.f, deltaTime);
				// cameraPosition += sf::Vector2f::Normalized(followTarget->GetPosition(), cameraPosition) * 400.f * deltaTime;
				if (sf::Vector2f::Distance(cameraPosition, followTarget->GetPosition()) <= 1.f)
					cameraPosition = followTarget->GetPosition();

				camera.setCenter(cameraPosition);
				
			}
			else
			{
				cameraPosition = followTarget->GetPosition();
				camera.setCenter(cameraPosition);
			}
			
		}
	}

	if (useCameraLimit)
	{
		CameraLimit();
	}
	
	if (useCameraShake)
		CameraShake(deltaTime);
}

bool Camera::SaveCsv(const std::string& filePath) const
{
	return false;
}

bool Camera::LoadCsv(const std::string& filePath)
{
	return false;
}
