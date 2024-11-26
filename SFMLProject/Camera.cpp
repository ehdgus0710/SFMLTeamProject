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
	
}

bool Camera::SaveCsv(const std::string& filePath) const
{
	return false;
}

bool Camera::LoadCsv(const std::string& filePath)
{
	return false;
}
