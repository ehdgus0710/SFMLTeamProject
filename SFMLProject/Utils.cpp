#include "stdafx.h"
#include "Utils.h"

std::mt19937 Utils::generator;
const float Utils::PI = acosf(-1.f);

void Utils::Init()
{
	std::random_device randomDevice;
	generator.seed(randomDevice());
}


float Utils::RandomRange(float min, float max)
{
	std::uniform_real_distribution<float>  distribution(min, max);
	return distribution(generator);
}

int Utils::RandomRange(int min, int max)
{
	std::uniform_int_distribution<int>  distribution(min, max);
	return distribution(generator);
}

float Utils::RandomValue()
{
	return RandomRange(0.f, 1.f);
}

sf::Vector2f Utils::RandomOnUnitCircle()
{
	float angle = RandomRange(0.f, 2.f * PI);
	return { cosf(angle), sinf(angle) };
}

sf::Vector2f Utils::RandomInUnitCircle()
{
	return RandomOnUnitCircle() * RandomValue();
}

float Utils::Max(float a, float b)
{
	return (a > b) ? a : b;
}

float Utils::Min(float a, float b)
{
	return (a < b) ? a : b;
}

float Utils::Clamp(float value, float min, float max)
{
	if (value < min)
		return min;
	if (value > max)
		return max;
	return value;
}

int Utils::Clamp(int value, int min, int max)
{
	if (value < min)
		return min;
	if (value > max)
		return max;
	return value;
}

float Utils::Lerp(float value, float end, float time)
{
	time = (time > 1.0f) ? 1.0f : ((time < 0.0f) ? 0.0f : time);
	return value * (1.0f - time) + end * time;
}

sf::Vector2f Utils::SetOrigin(sf::Transformable& object, Origins preset, const sf::FloatRect rect)
{
	sf::Vector2f newOrigin(rect.width, rect.height);
	newOrigin.x *= ((int)preset % 3) * 0.5f;
	newOrigin.y *= ((int)preset / 3) * 0.5f;
	object.setOrigin(newOrigin);
	return newOrigin;
}

sf::Vector2f Utils::SetOrigin(sf::Shape& object, Origins preset)
{
	return SetOrigin(object, preset, object.getLocalBounds());
}

sf::Vector2f Utils::SetOrigin(sf::Sprite& object, Origins preset)
{
	sf::FloatRect rect = object.getLocalBounds();
	sf::Vector2f newOrigin(rect.width, rect.height);

	newOrigin.x *= ((int)preset % 3) * 0.5f;
	newOrigin.y *= ((int)preset / 3) * 0.5f;

	object.setOrigin(newOrigin);

	return newOrigin;
}

sf::Vector2f Utils::SetOrigin(sf::Text& object, Origins preset)
{ 
	sf::FloatRect rect = object.getLocalBounds();
	sf::Vector2f newOrigin(rect.width, rect.height);

	newOrigin.x *= ((int)preset % 3) * 0.5f;
	newOrigin.y *= ((int)preset / 3) * 0.5f;

	object.setOrigin(newOrigin);

	return newOrigin;
}

sf::Vector2f Utils::SetOrigin(sf::Sprite& object, sf::IntRect& uvRect, Origins preset)
{
	sf::Vector2f newOrigin((float)uvRect.width, (float)uvRect.height);

	newOrigin.x *= ((int)preset % 3) * 0.5f;
	newOrigin.y *= ((int)preset / 3) * 0.5f;

	object.setOrigin(newOrigin);

	return newOrigin;
}
