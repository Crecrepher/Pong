#include "stdafx.h"
#include "Ball.h"
#include "InputMgr.h"
#include "Utils.h"
#include "Framework.h"
Ball::Ball()
{
}

Ball::~Ball()
{
}

const sf::Vector2f Ball::GetPos() const
{
    return position;
}

void Ball::SetPos(const sf::Vector2f pos)
{
    position = pos;
    shape.setPosition(position);
}

void Ball::Init()
{
	shape.setRadius({ 10.f });
	Utils::SetOrigin(shape, Origins::BC);
	shape.setFillColor(sf::Color::White);
	SetPos({ FRAMEWORK.GetWindowSize().x * 0.5f,FRAMEWORK.GetWindowSize().y - 25.f });
	speed = 0.f;
	direction = { 0.f,0.f };
}


sf::FloatRect Ball::GetBounds() const
{
	return shape.getGlobalBounds();
}

void Ball::Fire(sf::Vector2f dir, float s)
{
	direction = dir;
	speed = s;
}

void Ball::Update(float dt)
{
	SetPos(position + direction * speed * dt);
}

void Ball::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
}

const sf::Vector2f Ball::GetDir() const
{
	return direction;
}

void Ball::OnCollisionTop()
{
	direction.y = abs(direction.y);
}

void Ball::OnCollisionBottom()
{
	direction.y = -abs(direction.y);
}

void Ball::OnCollisionLeft()
{
	direction.x = abs(direction.y);
}

void Ball::OnCollisionRight()
{
	direction.x = -abs(direction.y);
}
