#include "stdafx.h"
#include "Animator.h"
#include "Animation.h"
#include "rapidcsv.h"


Animator::Animator(GameObject* owner, sf::Sprite& sprite)
	: sprite(&sprite)
	, currentAnimation(nullptr)
	, isPlaying(false)
	, owner(owner)
	, animationSpeed(1.f)
{
}

Animator::Animator(const Animator& other)
	: currentAnimation(nullptr)
	, uvRect(other.uvRect)
	, isPlaying(false)
	, owner(nullptr)
	, sprite(nullptr)
	, animationSpeed(1.f)
{
	animationMap.clear();
	for (auto& animation : other.animationMap)
	{
		Animation* copyAnimation = new Animation(*animation.second);
		copyAnimation->SetAnimator(this);
		animationMap.insert({ animation.first, copyAnimation });
	}
}

Animator::~Animator()
{
	for (auto& animation : animationMap)
	{
		delete animation.second;
	}

	animationMap.clear();
}

Animation* Animator::GetAnimation(const std::string& animationName)
{
	auto animation = animationMap.find(animationName);
	
	if (animationMap.end() == animation)
		return nullptr;

	return animation->second;
}

void Animator::CreateAnimation(const std::string& id, const std::string& animationName, const sf::Vector2u& rectSize, int frameCount, float frameTime, bool isRepeat)
{
	CreateAnimation(&ResourcesManager<sf::Texture>::GetInstance().Get(id), id, animationName, rectSize, frameCount, frameTime, isRepeat);
}

void Animator::CreateAnimation(const sf::Texture* texture, const std::string& id, const std::string& animationName, const sf::Vector2u& rectSize, int frameCount, float frameTime, bool isRepeat)
{
	if (animationMap.end() != animationMap.find(animationName))
		return;

	Animation* animation = new Animation(texture, id, animationName, rectSize, frameCount, frameTime, isRepeat);
	animationMap.insert({ animationName ,animation });
	animation->SetAnimator(this);

	if (currentAnimation == nullptr)
		StartAnimation(animation, isRepeat);
}

void Animator::AddAnimation(Animation* animation, const std::string& animationName)
{
	if (animationMap.find(animationName) != animationMap.end())
		return;

	animation->SetAnimator(this);
	animationMap.insert({ animationName, animation });
	animation->SetAnimationName(animationName);
	if (currentAnimation == nullptr)
		StartAnimation(animation, animation->IsRepeat());
}
void Animator::ChangeAnimation(const std::string& animationName, bool isRepeat, bool isUnscale, unsigned int index)
{
	auto animation = animationMap.find(animationName);
	if (animationMap.end() == animation)
		return;

	isPlaying = true;
	currentAnimation->SetRepeat(false);
	currentAnimation = animation->second;

	sprite->setTexture(*currentAnimation->GetTexture());
	currentAnimation->Play(animationSpeed, isRepeat);
	currentAnimation->SetUnScaleUpdate(isUnscale);
}

void Animator::StartAnimation(Animation* animation, bool isRepeat)
{
	isPlaying = true;
	currentAnimation = animation;
	sprite->setTexture(*currentAnimation->GetTexture(), true);
	currentAnimation->Play(isRepeat);
}

void Animator::Render(sf::RenderWindow& renderWindow)
{
	renderWindow.draw(*sprite);
}

void Animator::SetCurrentFrameRect(const sf::IntRect& rect)
{
	uvRect = rect;
	sprite->setTextureRect(uvRect);
}

void Animator::SetCurrentFrameInfo(const sf::Vector2u& size, const sf::IntRect& rect)
{
	uvRect = rect;
	rectSize = {(float)( size.x / uvRect.width) , (float)(size.y / uvRect.height )};
	sprite->setScale(rectSize * owner->GetScale());

	sprite->setTextureRect(uvRect);
	Utils::SetOrigin(*sprite, uvRect, owner->GetOrigins());
}

void Animator::SetAnimationSpeed(float speed)
{
	animationSpeed = speed;
}

void Animator::SetOrigin(Origins preset)
{
	if (preset == Origins::Custom)
		return;

	Utils::SetOrigin(*sprite, preset);
}

void Animator::SetOrigin(const sf::Vector2f& newOrigin)
{
	/*origins = Origins::Custom;
	originPosition = newOrigin;*/
	sprite->setOrigin(newOrigin);
}

void Animator::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale * rectSize;
	sprite->setScale(this->scale);
}


void Animator::SetPlaying(Animation* animation, bool isPlay)
{
	if (currentAnimation == animation)
		isPlaying = isPlay;
}

sf::FloatRect Animator::GetLocalBounds() const
{
	return sprite->getLocalBounds();
}

sf::FloatRect Animator::GetGlobalBounds() const
{
	return  sprite->getGlobalBounds();
}

void Animator::Play(bool isRepeat, bool isUnscale)
{
	isPlaying = true;
	currentAnimation->SetRepeat(isRepeat);
	currentAnimation->Play(animationSpeed, isRepeat);
	currentAnimation->SetUnScaleUpdate(isUnscale);
}

void Animator::Update(const float& deltaTime)
{
	if(isPlaying)
		currentAnimation->Update(deltaTime);
}

void Animator::Start()
{

}

bool Animator::Save() const
{
	

	return false;
}

bool Animator::Load()
{
	return false;
}

bool Animator::SaveCsv(const std::string& filePath) const
{
	std::ofstream outFile(filePath);

	outFile << "ANIMATIONCSVPATH,ANIMAIONID" << std::endl;

	for (auto& animation : animationMap)
	{
		outFile << std::endl;
		auto resource = ResourcesManager<Animation>::GetInstance().GetResource(animation.first);
		outFile << resource.GetFilePath() + "," + resource.GetKey();
	}
	return true;
}

bool Animator::LoadCsv(const std::string& filePath)
{
	rapidcsv::Document doc(filePath);

	std::string animationCsvPath;
	std::string animationId;
	for (int i = 1; i < doc.GetRowCount(); ++i)
	{
		auto row = doc.GetRow<std::string>(i);
		animationCsvPath = row[0];
		animationId = row[1];

		ResourcesManager<Animation>::GetInstance().Load(animationId, animationCsvPath);
		Animation* animation = new Animation(ResourcesManager<Animation>::GetInstance().Get(animationId));
		AddAnimation(animation, animationId);
	}
	return true;
}
