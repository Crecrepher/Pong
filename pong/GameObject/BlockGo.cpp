#include "stdafx.h"
#include "BlockGo.h"
#include "BouncyBall.h"

BlockGo::BlockGo(const std::string n)
	:RectGo(n), blockHP(1)
{
}

BlockGo::~BlockGo()
{
}

void BlockGo::SetPosition(float x, float y)
{
	RectGo::SetPosition(x, y);
	blockUp.SetPosition(GetPosition().x, GetPosition().y-(rectangle.getSize().y/2)+0.5f);
	blockDown.SetPosition(GetPosition().x, GetPosition().y + (rectangle.getSize().y / 2) - 0.5f);
	blockLeft.SetPosition(GetPosition().x - (rectangle.getSize().x / 2) + 0.5f, GetPosition().y);
	blockRight.SetPosition(GetPosition().x + (rectangle.getSize().x / 2) - 0.5f, GetPosition().y);
}

void BlockGo::SetPosition(const sf::Vector2f& p)
{
	RectGo::SetPosition(p);
	blockUp.SetPosition(GetPosition().x, GetPosition().y - (rectangle.getSize().y / 2) + 0.5f);
	blockDown.SetPosition(GetPosition().x, GetPosition().y + (rectangle.getSize().y / 2) - 0.5f);
	blockLeft.SetPosition(GetPosition().x - (rectangle.getSize().x / 2) + 0.5f, GetPosition().y);
	blockRight.SetPosition(GetPosition().x + (rectangle.getSize().x / 2) - 0.5f, GetPosition().y);
}


void BlockGo::SetSize(const sf::Vector2f& size)
{
	RectGo::SetSize(size);
	blockUp.SetSize(size.x,1.f);
	blockDown.SetSize(size.x, 1.f);
	blockLeft.SetSize(1.f, size.y);
	blockRight.SetSize(1.f, size.y);
}

void BlockGo::Init()
{
	RectGo::Init();
}

void BlockGo::Reset()
{
	RectGo::Reset();
}

void BlockGo::Release()
{
	RectGo::Release();
}

void BlockGo::Update(float dt)
{
	RectGo::Update(dt);
}

void BlockGo::Draw(sf::RenderWindow& window)
{
	RectGo::Draw(window);
	if (blockHP < 0)
	{
		SetActive(false);
		blockUp.SetActive(false);
		blockDown.SetActive(false);
		blockLeft.SetActive(false);
		blockRight.SetActive(false);
	}
}


bool BlockGo::BlockNBall(const sf::FloatRect& rect, BouncyBall* ball)
{
	sf::Vector2f rectHalfSize(rect.width / 2.f, rect.height / 2.f);
	sf::Vector2f circleDistance(
		std::abs(ball->GetPosition().x - rect.left - rectHalfSize.x),
		std::abs(ball->GetPosition().y - rect.top - rectHalfSize.y)
	);

	if (circleDistance.x > (rectHalfSize.x + ball->circle.getRadius()) ||
		circleDistance.y > (rectHalfSize.y + ball->circle.getRadius()))
	{
		return false;
	}

	if (circleDistance.x <= rectHalfSize.x ||
		circleDistance.y <= rectHalfSize.y)
	{
		return true;
	}

	float cornerDistanceSq = std::pow(circleDistance.x - rectHalfSize.x, 2) +
		std::pow(circleDistance.y - rectHalfSize.y, 2);

	return cornerDistanceSq <= std::pow(ball->circle.getRadius(), 2);
}

void BlockGo::CheckBlock(BouncyBall* ball)
{
	if (BlockNBall(blockUp.frect,ball))
	{
		ball->Yup();
		blockHP--;
	}
	else if (BlockNBall(blockDown.frect, ball))
	{
		ball->Ydown();
		blockHP--;
	}
	else if (BlockNBall(blockLeft.frect, ball))
	{
		ball->Xleft();
		blockHP--;
	}
	else if (BlockNBall(blockRight.frect, ball))
	{
		ball->Xright();
		blockHP--;
	}
}

bool BlockGo::isBreak()
{
	return blockHP==0;
}
