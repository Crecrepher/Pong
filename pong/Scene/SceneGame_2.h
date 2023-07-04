#pragma once
#include "Scene.h"
#include "BlockGo.h"
#include "EffectGo.h"
#include <sstream>
#include "Bat.h"
#include "Ball.h"

class SceneGame2 : public Scene
{
protected:
	Bat bat;
	Ball ball;
	sf::Text hud;

	bool playerBound = false;
	bool ballActive = false;
	int score = 0;
	int life = 3;

public:
	SceneGame2();
	virtual ~SceneGame2() override;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
};

