#pragma once
#include <SFML/Graphics.hpp>
class Ball
{
protected:
	sf::CircleShape shape;
	sf::Vector2f direction;

	sf::Vector2f position;
	float speed;
	bool ballActive = false;

public:
	Ball();
	~Ball();

	const sf::Vector2f GetPos() const;
	void SetPos(const sf::Vector2f pos);

	void Init();
	void Fire(sf::Vector2f dir, float s);
	sf::FloatRect GetBounds() const;

	void Update(float dt);
	void Draw(sf::RenderWindow& window);

	const sf::Vector2f GetDir() const;

	void OnCollisionTop();
	void OnCollisionBottom();
	void OnCollisionLeft();
	void OnCollisionRight();
};

