#include "stdafx.h"
#include "PongPlayerGo.h"

PongPlayerGo::PongPlayerGo(const std::string n) :BlockGo(n)
{
	isPlayer = true;
}

PongPlayerGo::~PongPlayerGo()
{
}

void PongPlayerGo::Init()
{
	BlockGo::Init();
}

void PongPlayerGo::Reset()
{
	BlockGo::Reset();
}

void PongPlayerGo::Release()
{
	BlockGo::Release();
}

void PongPlayerGo::Update(float dt)
{
	BlockGo::Update(dt);
}

void PongPlayerGo::Draw(sf::RenderWindow& window)
{
	BlockGo::Draw(window);
}
