#include "stdafx.h"
#include "SceneGame_1.h"
#include "SceneMgr.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
#include "GameObject.h"
#include "Framework.h"

#include "BouncyBall.h"
#include "TextGo.h"
#include "PongPlayerGo.h"


SceneGame::SceneGame() : Scene(SceneId::Game1), score(0),live(3),
playerWidth(100.f), playerThick(20.f), playerDir(Direction::None),
playerSpd(1500.f),pause(true)
{
	resources.push_back(std::make_tuple(ResourceTypes::Texture, "graphics/player4.png"));

}

SceneGame::~SceneGame()
{
}

void SceneGame::Init()
{
	Release();
	AddGo(new TextGo("score"));
	AddGo(new PongPlayerGo("Player"));
	AddGo(new BouncyBall("Ball"));
	AddGo(new TextGo("Score"));
	for (int i = 0; i < 25; i++)
	{
		std::string str = "Block" + std::to_string(i);
		AddGo(new BlockGo(str));
	}
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


	PongPlayerGo* findRect = (PongPlayerGo*)FindGo("Player");
	findRect->SetSize(sf::Vector2f(playerWidth, playerThick));
	findRect->SetOrigin(Origins::MC);
	findRect->SetPosition(FRAMEWORK.GetWindowSize().x * 0.5f, FRAMEWORK.GetWindowSize().y * 0.9f);
	findRect->rectangle.setFillColor(sf::Color::White);
	findRect->sortLayer = 2;
	findRect->SetPlayer();

	BouncyBall* ball= (BouncyBall*)FindGo("Ball");
	ball->SetBallSize(10.f);
	ball->circle.setFillColor(sf::Color::White);
	ball->sortLayer = 2;
	ball->Reset();

	TextGo* findTGo = (TextGo*)FindGo("Score");
	findTGo->text.setFont(*RESOURCE_MGR.GetFont("fonts/DS-DIGI.ttf"));
	findTGo->text.setString("PRESS ENTER");
	findTGo->text.setCharacterSize(75);
	findTGo->text.setFillColor(sf::Color::White);
	Utils::SetOrigin(findTGo->text, Origins::TL);
	findTGo->text.setPosition(25.f,5.f);
	findTGo->sortLayer = 1;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			std::string str = "Block" + std::to_string((i*5)+j);
			BlockGo* findBGo = (BlockGo*)FindGo(str);
			findBGo->SetActive(true);
			findBGo->SetBlockHp(1);
			findBGo->SetSize(sf::Vector2f(playerWidth, playerThick));
			findBGo->SetOrigin(Origins::MC);
			findBGo->SetPosition(FRAMEWORK.GetWindowSize().x * 0.1 + (j * playerWidth)+150.f*j,
				FRAMEWORK.GetWindowSize().y * 0.15f+ (i * playerThick) + 50.f*i);
			findBGo->rectangle.setFillColor(sf::Color::White);
			findBGo->sortLayer = 2;
		}
	}


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

	PongPlayerGo* findRect = (PongPlayerGo*)FindGo("Player");
	BouncyBall* ball = (BouncyBall*)FindGo("Ball");
	TextGo* findTGo = (TextGo*)FindGo("Score");
	pause = ball->IsDead();
	for (int i = 0; i < 25; i++)
	{
		std::string str = "Block" + std::to_string(i);
		BlockGo* findBGo = (BlockGo*)FindGo(str);
		findBGo->CheckBlock(ball);
	}

	if (live - ball->LifeLost() <= 0)
	{
		findTGo->text.setString("Game Over");
		return;
	}

	if (INPUT_MGR.GetKey(sf::Keyboard::Left) && findRect->GetPosition().x > playerWidth / 2)
	{
		findRect->SetPosition(findRect->GetPosition().x - playerSpd * dt,
			findRect->GetPosition().y);
		playerDir = Direction::Left;
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::Right) && findRect->GetPosition().x < FRAMEWORK.GetWindowSize().x - playerWidth / 2)
	{
		findRect->SetPosition(findRect->GetPosition().x + playerSpd * dt,
			findRect->GetPosition().y);
		playerDir = Direction::Right;
	}

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Return) ||
		INPUT_MGR.GetKeyDown(sf::Keyboard::Space))
	{
		pause = false;
	}
	if (pause)
	{
		ball->SetPosition(findRect->GetPosition() + sf::Vector2f(0, -playerThick));
		return;
	}
	/////////////////////////////////////////////////////////////////
	Scene::Update(dt);


	std::stringstream scoreText;
	scoreText << "SCORE " << score <<
		"\tLIFE " << live - ball->LifeLost();
	findTGo->text.setString(scoreText.str());

	//if (ball->GetPosition().y >= findRect->GetPosition().y - playerThick
	//	&& ball->GetPosition().y <= findRect->GetPosition().y + playerThick)
	//{
	//	if (ball->GetPosition().x >= findRect->GetPosition().x - playerWidth / 2
	//		&& ball->GetPosition().x <= findRect->GetPosition().x + playerWidth / 2)
	//	{

	//		if (ball->GetDir().y > 0)
	//		{
	//			score++;
	//			if (playerDir == ball->ballCurrentDir)
	//			{
	//				if (ball->ballCurrentDir == Direction::Left &&
	//					ball->direction.y >= 0.2)
	//				{
	//					ball->direction.x = ball->direction.x - 0.3;
	//					ball->direction.y = -2 - ball->direction.x;
	//				}
	//				else if (ball->ballCurrentDir == Direction::Right)
	//				{
	//					ball->direction.x = ball->direction.x + 0.3;
	//					ball->direction.y = -2 + ball->direction.x;
	//				}
	//			}
	//			else if (playerDir != ball->ballCurrentDir &&
	//				playerDir != Direction::None)
	//			{
	//				if (ball->ballCurrentDir == Direction::Left)
	//				{
	//					ball->direction.x = ball->direction.x + 0.3;
	//					ball->direction.y = -2 - ball->direction.x;
	//				}
	//				else if (ball->ballCurrentDir == Direction::Right)
	//				{
	//					ball->direction.x = ball->direction.x - 0.3;
	//					ball->direction.y = -2 + ball->direction.x;
	//				}
	//			}

	//		}
	//	}
	//}

	findRect->CheckBlock(ball);


}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);

}

