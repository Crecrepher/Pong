#pragma once
#include <SFML/Graphics.hpp>
class Bat
{
protected:
	float speed = 1000.f;
	sf::Vector2f direction;

	sf::Vector2f position;
	sf::RectangleShape shape;
public:
	Bat() = default;
	~Bat() = default;

	const sf::Vector2f& GetPos() const;
	void SetPos(const sf::Vector2f& pos);

	sf::FloatRect GetBounds() const;

	void Init();

	void Update(float dt);
	void Draw(sf::RenderWindow& window);
};

