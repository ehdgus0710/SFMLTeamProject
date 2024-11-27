#include "stdafx.h"
#include "Animation.h"
#include "GameObject.h"
#include "Animator.h"
#include "rapidcsv.h"

Animation::Animation()
	: texture(nullptr)
	, totalFrameTime(0.f)
	, currentAnimationTime(0.f)
	, frameCount(0)
	, currentIndex(0)
	, isRepeat(false)
	, isPlaying(false)
	, isUnscale(false)
	, animator(nullptr)
	, animationSpeed(1.f)
{
}

Animation::Animation(const sf::Texture* texture, const std::string& textureID,const std::string& animationName ,const sf::Vector2u& rectSize, int frameCount, float frameTime, bool isRepeat)
	: texture(texture)
	, totalFrameTime(0.f)
	, currentAnimationTime(0.f)
	, frameCount(frameCount)
	, currentIndex(0)
	, isRepeat(isRepeat)
	, isPlaying(false)
	, isUnscale(false)
	, animator(nullptr)
	, animationID(animationName)
	, textureID(textureID)
{
	frameInfoVector.clear();

	sf::Vector2u textureSize = texture->getSize();
	sf::Vector2u textureFrameCount = { textureSize.x / rectSize.x ,textureSize.y / rectSize.y };

	int totalCount = textureFrameCount.x * textureFrameCount.y;
	int count = 0;
	int topPos = 0;

	for (int i = 0; i < frameCount; ++i)
	{
		AnimationInfo frameInfo;

		frameInfo.uvRect.left = rectSize.x * count;
		frameInfo.uvRect.top = rectSize.y * topPos;
		frameInfo.uvRect.width = rectSize.x;
		frameInfo.uvRect.height = rectSize.y;

		frameInfo.duration = frameTime;
		frameInfo.rectSize = rectSize;

		totalFrameTime += frameTime;
		frameInfoVector.push_back(frameInfo);

		++count;
		if (count == textureFrameCount.x)
		{
			count = 0;
			++topPos;
		}
	}
}

Animation::Animation(const Animation& other)
	: animator(nullptr)
	, texture(other.texture)
	, frameCount(other.frameCount)
	, currentIndex(0)
	, totalFrameTime(other.totalFrameTime)
	, currentAnimationTime(0.f)
	, isUnscale(false)
	, isPlaying(false)
	, isRepeat(false)
{	
	int count = (int)other.frameInfoVector.size();
	for (int i = 0; i < count; ++i)
	{
		AnimationInfo info = other.frameInfoVector[i];
		frameInfoVector.push_back(info);
	}
}

Animation::~Animation()
{
	frameInfoVector.clear();
}

void Animation::CreateAnimationInfo(const sf::Texture* texture, const std::string& textureID, const sf::Vector2u& rectSize, int frameCount, float frameTime, bool isRepeat)
{
	this->textureID = textureID;
	sf::Vector2u textureSize = texture->getSize();
	sf::Vector2u textureFrameCount = { textureSize.x / rectSize.x ,textureSize.y / rectSize.y };
	int count = 0;
	int topPos = 0;

	for (int i = 0; i < frameCount; ++i)
	{
		AnimationInfo frameInfo;

		frameInfo.uvRect.left = rectSize.x * i;
		frameInfo.uvRect.top = 0;
		frameInfo.uvRect.width = rectSize.x;
		frameInfo.uvRect.height = rectSize.y;

		frameInfo.duration = frameTime;
		frameInfo.rectSize = rectSize;

		totalFrameTime += frameTime;
		frameInfoVector.push_back(frameInfo);

		++count;
		if (count == textureFrameCount.x)
		{
			count = 0;
			++topPos;
		}
	}
}

void Animation::CreateAnimationInfo(const sf::Texture* texture, const std::string& textureID, const std::string& animationName, const std::vector<AnimationInfo>& frames)
{
	this->textureID = textureID;
	this->texture = texture;
	animationID = animationName;

	frameInfoVector = frames;
	frameCount = (int)frames.size();

	for (auto& frame : frameInfoVector)
	{
		totalFrameTime += frame.duration;
	}
}


void Animation::Play(float speed, bool isRepeat)
{
	animationSpeed = speed;
	Reset();
	// animationStartEvnet;
	this->isRepeat = isRepeat;
	isPlaying = true;

	animator->SetCurrentFrameInfo(frameInfoVector[0].rectSize, frameInfoVector[0].uvRect);
	//if (animator != nullptr)
	//{
	//	//animator->SetCurrentFrameRect();
	//}
}

void Animation::Stop()
{
	isPlaying = false;
	animator->SetPlaying(isPlaying);
}

void Animation::Reset()
{
	currentIndex = 0;
	currentAnimationTime = 0.f;
}

void Animation::Update(float deltaTime)
{
	if (!isPlaying)
		return;

	if (isUnscale)
		currentAnimationTime += TimeManager::GetInstance().GetUnScaleDeletaTime() * animationSpeed;
	else
		currentAnimationTime += deltaTime * animationSpeed;

	if (currentAnimationTime >= frameInfoVector[currentIndex].duration)
	{
		for (auto& endEvent : frameInfoVector[currentIndex].endEvents)
		{
			if (endEvent)
				endEvent();
		}
		currentAnimationTime -= frameInfoVector[currentIndex++].duration;

		if (currentIndex == frameCount)
		{
			if (isRepeat)
				currentIndex = 0;
			else
			{
				Stop();
				return;
			}

		}

		animator->SetCurrentFrameInfo(frameInfoVector[currentIndex].rectSize, frameInfoVector[currentIndex].uvRect);
		for (auto& startEvent : frameInfoVector[currentIndex].startEvents)
		{
			if (startEvent)
				startEvent();
		}
		//animator->SetCurrentFrameRect(frameInfoVector[currentIndex].uvRect);
	}
}

void Animation::AddAnimationInfo(const AnimationInfo& animationInfo, unsigned int index)
{
	if (frameCount <= index)
	{
		AddAnimationInfo(animationInfo);
	}
	else
	{
		auto iter = frameInfoVector.begin() + index;
		frameInfoVector.insert(iter, animationInfo);

		totalFrameTime += animationInfo.duration;
		++frameCount;
	}
}

void Animation::AddAnimationInfo(const AnimationInfo& animationInfo)
{
	frameInfoVector.push_back(animationInfo);

	totalFrameTime += animationInfo.duration;
	++frameCount;
}

void Animation::SetAnimationInfo(const AnimationInfo& animationInfo, unsigned int index)
{
	if (index >= frameCount)
		return;

	frameInfoVector[index] = animationInfo;
}

void Animation::SetRectSize(sf::Vector2u rectSize, unsigned int index)
{
	if (index >= frameCount)
		return;

	frameInfoVector[index].rectSize = rectSize;
}

void Animation::SetAnimationStartEvent(std::function<void()> startEvent, unsigned int index)
{
	if (index >= frameCount)
		return;

	frameInfoVector[index].startEvents.push_back(startEvent);
	// frameInfoVector[index].animationEvent = event;
}

void Animation::SetAnimationEndEvent(std::function<void()> endEvent, unsigned int index)
{
	if (index >= frameCount)
		return;

	frameInfoVector[index].endEvents.push_back(endEvent);
}

void Animation::ClearStartEvent(unsigned int index)
{
	frameInfoVector[index].startEvents.clear();
}

void Animation::ClearEndEvent(unsigned int index)
{
	frameInfoVector[index].endEvents.clear();
}


bool Animation::SaveCSV(const std::string& filePath)
{
	std::ofstream outFile(filePath);

	outFile << "TEXTUREID,ANIMAIONID,REPEAT(0: true, 1: false)" << std::endl;
	outFile << textureID << "," << animationID << "," << std::to_string((int)isRepeat) << std::endl;

	for (auto& frame : frameInfoVector)
	{
		outFile << std::endl;
		outFile << frame.textureID;
		outFile << "," + std::to_string(frame.rectSize.x);
		outFile << "," + std::to_string(frame.rectSize.y);
		outFile << "," + std::to_string(frame.uvRect.left);
		outFile << "," + std::to_string(frame.uvRect.top);
		outFile << "," + std::to_string(frame.uvRect.width);
		outFile << "," + std::to_string(frame.uvRect.height);
		outFile << "," + std::to_string(frame.duration);
	}
	return true;
}

bool Animation::loadFromFile(const std::string& filePath)
{
	rapidcsv::Document doc(filePath);

	textureID = doc.GetCell<std::string>(0, 0);
	animationID = doc.GetCell<std::string>(1, 0);
	isRepeat = (bool)doc.GetCell<int>(2, 0);

	frameInfoVector.clear();
	for (int i = 2; i < doc.GetRowCount(); ++i)
	{
		auto row = doc.GetRow<std::string>(i);

		frameInfoVector.push_back({ row[0] , {(unsigned int)std::stoi(row[1]) ,(unsigned int)std::stoi(row[2])},  {  std::stoi(row[3]) ,std::stoi(row[4]) , std::stoi(row[5]) ,std::stoi(row[6]) }, std::stof(row[7]) });
		totalFrameTime += frameInfoVector[i - 2].duration;
	}
	frameCount = (int)frameInfoVector.size();

	texture = &ResourcesManager<sf::Texture>::GetInstance().Get(textureID);

	return true;
}