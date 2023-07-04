#include "stdafx.h"
#include "SceneGame_2.h"
#include "SceneMgr.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
#include "GameObject.h"
#include "Framework.h"
#include <sstream>

#include "TextGo.h"

SceneGame2::SceneGame2() : Scene(SceneId::Game2)
{
}

SceneGame2::~SceneGame2()
{
}

void SceneGame2::Init()
{
	Release();
	bat.Init();
	ball.Init();

	hud.setFont(*RESOURCE_MGR.GetFont("fonts/DS-DIGI.ttf"));
	hud.setCharacterSize(50);
	hud.setFillColor(sf::Color::White);
	hud.setPosition(20, 20);
}

void SceneGame2::Release()
{
}

void SceneGame2::Enter()
{
	Scene::Enter();
	bat.Init();
}

void SceneGame2::Exit()
{
	Scene::Exit();
}

void SceneGame2::Update(float dt)
{
	if (!ballActive && INPUT_MGR.GetKeyDown(sf::Keyboard::Space))
	{
		ballActive = true;
		ball.Fire(Utils::Normalize({1.f,-1.f}),1000.f);
	}
	Scene::Update(dt);
	bat.Update(dt);


	if (!ballActive)
	{
		ball.SetPos(bat.GetPos());
	}
	ball.Update(dt);

	//충돌체크
	const sf::FloatRect ballRect = ball.GetBounds();
	if (ballRect.top < 0.f)
	{
		// 위
		ball.OnCollisionTop();
	}
	else if (ballRect.top + ballRect.height >720.f)
	{
		//아래
		ball.OnCollisionBottom();	
		--life;

		ballActive = false;
		ball.Init();
		if (life == 0)
		{
			bat.Init();
			score = 0;
			life = 3;
		}
	}
	else if (ballRect.left < 0.f)
	{
		// 왼쪽
		ball.OnCollisionLeft();
	}
	else if (ballRect.left + ballRect.width >1280.f)
	{
		// 오른쪽
		ball.OnCollisionRight();
	}

	if (ballRect.intersects(bat.GetBounds())&& !playerBound && ball.GetDir().y>0)
	{
		ball.OnCollisionBottom();
		score++;
		playerBound = true;
	}
	else
	{
		playerBound = false;
	}

	std::stringstream ss;
	ss << "Score: " << score << "\tLife: " << life;
	hud.setString(ss.str());
}

void SceneGame2::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	bat.Draw(window);
	ball.Draw(window);
	window.draw(hud);
}

