#include "Utils.h"
#include "stdafx.h"
#include "Utils.h"

std::random_device Utils::rd;
std::mt19937 Utils::gen(Utils::rd());

int Utils::RandomRange(int min, int maxExclude)
{
	std::uniform_int_distribution<> dist(min, maxExclude);
	return dist(gen);
}

float Utils::RandomRange(float min, float max)
{
	std::uniform_real_distribution<> dist(min, max);
	return (float)dist(gen);
}

sf::Vector2f Utils::RandomOnCircle(float radius)
{
	sf::Vector2f vec(RandomRange(-1.0f,1.0f),RandomRange(-1.0f,1.0f));
	vec = Normalize(vec) * radius;
	return vec;
}

sf::Vector2f Utils::RandomInCircle(float radius)
{
	return RandomOnCircle(radius)* RandomValue();
}

float Utils::RandomValue()
{
	return RandomRange(0.f, 1.f);
}

void Utils::SetOrigin(sf::Sprite& sprite, Origins origin)
{
	SetOrigin(sprite, origin, sprite.getLocalBounds());
}

void Utils::SetOrigin(sf::Text& text, Origins origin)
{
	SetOrigin(text, origin, text.getLocalBounds());
}

void Utils::SetOrigin(sf::Shape& shape, Origins origin)
{
	SetOrigin(shape, origin, shape.getLocalBounds());
 }

void Utils::SetOrigin(sf::Transformable& obj, Origins origin, const sf::FloatRect& rect)
{
	sf::Vector2f originPos(rect.width, rect.height);
	originPos.x *= ((int)origin % 3) * 0.5f;
	originPos.y *= ((int)origin / 3) * 0.5f;
	obj.setOrigin(originPos);
}

float Utils::SqrMagnitude(const sf::Vector2f& vec)
{
	return vec.x * vec.x + vec.y * vec.y;
}

float Utils::Magnitude(const sf::Vector2f& vec)
{//가로세로로 만들어진 벡터의 길이구함
	return sqrt(vec.x * vec.x + vec.y * vec.y);
	//sqrt = 루트
}


sf::Vector2f Utils::Normalize(const sf::Vector2f& vec)
{//벡터 길이를 1로만듬
	float mag = Magnitude(vec);
	if (mag == 0.f)
	{
		return vec;
	}
	return vec / mag;
}

float Utils::Distance(const sf::Vector2f& a, const sf::Vector2f& b)
{
	return Magnitude(a-b);
}

float Utils::Angle()
{
	return 0.0f;
}
