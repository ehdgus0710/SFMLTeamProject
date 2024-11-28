#pragma once
class Utils
{
private:
	static std::mt19937 generator;

public:
	const static float PI;

public:
	static void Init();

	static float RandomRange(float min, float max);
	static int RandomRange(int min, int max);
	static float RandomValue();				// 확률 구현 할때 자주 사용
	static sf::Vector2f RandomOnUnitCircle();
	static sf::Vector2f RandomInUnitCircle();

	static float RadianToDegree(float radian);
	static float DegreeToRadian(float degree);
	static float AngleRadian(const sf::Vector2f& vec);
	static float Angle(const sf::Vector2f& vec);

	static float Max(float a, float b);
	static float Min(float a, float b);

	static float Clamp(float value, float min, float max);
	static int Clamp(int value, int min, int max);
	static float Lerp(float value, float end, float time);

	// Origin
	static sf::Vector2f SetOrigin(sf::Transformable& object, Origins preset, const sf::FloatRect bound);
	static sf::Vector2f SetOrigin(sf::Shape& object, Origins preset);
	static sf::Vector2f SetOrigin(sf::Sprite& object, Origins preset);
	static sf::Vector2f SetOrigin(sf::Text& object, Origins preset);
	static sf::Vector2f SetOrigin(sf::Sprite& object, sf::IntRect& uvRect, Origins preset);
};

struct Rectangle
{
	float leftPosition;
	float rightPosition;
	float topPosition;
	float bottomPosition;

	Rectangle()
		: leftPosition(0.f)
		, rightPosition(0.f)
		, topPosition(0.f)
		, bottomPosition(0.f)
	{

	}

	Rectangle(float left, float rgiht, float top, float bottom)
		: leftPosition(left)
		, rightPosition(rgiht)
		, topPosition(top)
		, bottomPosition(bottom)
	{

	}

	Rectangle(const sf::Vector2f& position, const sf::Vector2f& size)
		: leftPosition(position.x - size.x * 0.5f)
		, rightPosition(position.x + size.x * 0.5f)
		, topPosition(position.y - size.y * 0.5f)
		, bottomPosition(position.y + size.y * 0.5f)
	{

	}

	Rectangle(const sf::Vector2f& size)
		: leftPosition(-size.x * 0.5f)
		, rightPosition(size.x * 0.5f)
		, topPosition(-size.y * 0.5f)
		, bottomPosition(size.y * 0.5f)
	{

	}
};