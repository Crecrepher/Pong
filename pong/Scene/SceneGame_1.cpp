#include "stdafx.h"
#include "SceneGame_1.h"
#include "SceneMgr.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
#include "GameObject.h"
#include "Framework.h"

#include "RectGo.h"
#include "BouncyBall.h"
#include "TextGo.h"

SceneGame::SceneGame() : Scene(SceneId::Game1), score(0),live(3),
playerWidth(100.f), playerThick(20.f), playerDir(Direction::None),
playerSpd(1500.f),pause(true)
{

}

SceneGame::~SceneGame()
{
}

void SceneGame::Init()
{
	Release();
	AddGo(new TextGo("score"));
	AddGo(new RectGo("Player"));
	AddGo(new BouncyBall("Ball"));
	AddGo(new TextGo("Score"));

	for (auto go : gameObjects)
	{
		go->Init();
	}
}

void SceneGame::Release()
{
	for (auto go : gameObjects)
	{
		//go->Release();
		delete go;
	}
}

void SceneGame::Enter()
{
	Scene::Enter();

	pause = true;
	score = 0;
	live = 3;
	playerWidth = 100.f;
	playerThick = 20.f;
	

	RectGo* findRect = (RectGo*)FindGo("Player");
	findRect->rectangle.setSize(sf::Vector2f(playerWidth, playerThick));
	findRect->SetOrigin(Origins::MC);
	findRect->SetPosition(FRAMEWORK.GetWindowSize().x * 0.5f, FRAMEWORK.GetWindowSize().y * 0.9f);
	findRect->rectangle.setFillColor(sf::Color::White);
	findRect->sortLayer = 2;

	BouncyBall* ball= (BouncyBall*)FindGo("Ball");
	ball->SetBallSize(10.f);
	ball->circle.setFillColor(sf::Color::White);
	findRect->sortLayer = 2;
	ball->Reset();

	TextGo* findTGo = (TextGo*)FindGo("Score");
	findTGo->text.setFont(*RESOURCE_MGR.GetFont("fonts/DS-DIGI.ttf"));
	findTGo->text.setString("PRESS ENTER");
	findTGo->text.setCharacterSize(75);
	findTGo->text.setFillColor(sf::Color::White);
	Utils::SetOrigin(findTGo->text, Origins::TL);
	findTGo->text.setPosition(25.f,5.f);
	findTGo->sortLayer = 1;
}

void SceneGame::Exit()
{
	Scene::Exit();

}

void SceneGame::Update(float dt)
{
	playerDir = Direction::None;
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Escape))
	{
		SCENE_MGR.ChangeScene(SceneId::Title);
	}

	RectGo* findRect = (RectGo*)FindGo("Player");
	BouncyBall* ball = (BouncyBall*)FindGo("Ball");
	TextGo* findTGo = (TextGo*)FindGo("Score");

	if (live - ball->LifeLost() <= 0)
	{
		findTGo->text.setString("Game Over");
		return;
	}

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Return))
	{
		pause = false;
	}
	if (pause)
	{
		return;
	}
	Scene::Update(dt);
	
	
	std::stringstream scoreText;
	scoreText << "SCORE " << score <<
		"\tLIFE " << live - ball->LifeLost();
	findTGo->text.setString(scoreText.str());

	

	
	if (INPUT_MGR.GetKey(sf::Keyboard::Left)&& findRect->GetPosition().x> playerWidth/2)
	{
		findRect->SetPosition(findRect->GetPosition().x- playerSpd *dt,
			findRect->GetPosition().y);
		playerDir = Direction::Left;
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::Right)&& findRect->GetPosition().x < FRAMEWORK.GetWindowSize().x-playerWidth / 2)
	{
		findRect->SetPosition(findRect->GetPosition().x + playerSpd * dt,
			findRect->GetPosition().y);
		playerDir = Direction::Right;
	}
	

	if (ball->GetPosition().y >= findRect->GetPosition().y-playerThick
		&& ball->GetPosition().y <= findRect->GetPosition().y + playerThick)
	{
		if (ball->GetPosition().x >= findRect->GetPosition().x - playerWidth/2
			&& ball->GetPosition().x <= findRect->GetPosition().x + playerWidth/2)
		{
			
			if (ball->GetDir().y>0)
			{
				score++;
				if (playerDir == ball->ballCurrentDir)
				{
					if (ball->ballCurrentDir == Direction::Left)
					{
						ball->direction.x = ball->direction.x - 0.3;
						ball->direction.y = -2 - ball->direction.x;
					}
					else if (ball->ballCurrentDir == Direction::Right)
					{
						ball->direction.x = ball->direction.x + 0.3;
						ball->direction.y = -2 + ball->direction.x;
					}
				}
				else if (playerDir != ball->ballCurrentDir && playerDir != Direction::None)
				{
					if (ball->ballCurrentDir == Direction::Left)
					{
						ball->direction.x = ball->direction.x + 0.3;
						ball->direction.y = -2 - ball->direction.x;
					}
					else if (ball->ballCurrentDir == Direction::Right)
					{
						ball->direction.x = ball->direction.x - 0.3;
						ball->direction.y = -2 + ball->direction.x;
					}
				}
				ball->Yup();
			}
		}
	}


}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
