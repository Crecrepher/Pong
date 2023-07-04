#pragma once
#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>
#include "Defines.h"

class Utils
{
private:
	static std::random_device rd;
	static std::mt19937 gen;

public:
	static int RandomRange(int min, int maxExclude);
	static float RandomRange(float min, float max);
	static sf::Vector2f RandomOnCircle(float radius);
	static sf::Vector2f RandomInCircle(float radius);
	static float RandomValue();//0.0f ~1.0f

	static void SetOrigin(sf::Sprite& sprite, Origins origin);
	static void SetOrigin(sf::Text& text, Origins origin);
	static void SetOrigin(sf::Shape& shape, Origins origin);

	static void SetOrigin(sf::Transformable& obj, Origins origin, const sf::FloatRect& rect);

	// Vector2
	static float SqrMagnitude(const sf::Vector2f& vec);
	static float Magnitude(const sf::Vector2f& vec);
	static sf::Vector2f Normalize(const sf::Vector2f& vec);
	static float Distance(const sf::Vector2f& a, const sf::Vector2f& b); //거리 구하는 함수

	//함수 2개만들기 0.0~1.0
	//동그라미 태두리에 하나
	//동그라미 원안에 어디든 하나
};

