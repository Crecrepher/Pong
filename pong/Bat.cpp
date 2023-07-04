#include "stdafx.h"
#include "Bat.h"
#include "InputMgr.h"
#include "Utils.h"

const sf::Vector2f& Bat::GetPos() const
{
	return position;
}

void Bat::SetPos(const sf::Vector2f& pos)
{
	position = pos;
	shape.setPosition(position);
}

sf::FloatRect Bat::GetBounds() const
{
	return shape.getGlobalBounds();
}

void Bat::Init()
{
	shape.setSize({ 100.f,5.f });
	Utils::SetOrigin(shape, Origins::TC);
	shape.setFillColor(sf::Color::White);
	SetPos({1280.f * 0.5f,720.f-25.f});
	speed = 1000.f;
	direction = { 0.f,0.f };
}

void Bat::Update(float dt)
{
	direction.x = 0.f;
	if (INPUT_MGR.GetKey(sf::Keyboard::A))
	{
		direction.x -= 1.f;
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::D))
	{
		direction.x += 1.f;
	}
	position += direction * speed * dt;
	SetPos(position);
}

void Bat::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
}
