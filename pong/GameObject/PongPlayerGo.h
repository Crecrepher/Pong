#pragma once
#include "BlockGo.h"

class PongPlayerGo : public BlockGo
{
private:

public:
	PongPlayerGo(const std::string n);
	~PongPlayerGo();

	virtual void Init()override;
	virtual void Reset()override;
	virtual void Release() override;
	virtual void Update(float dt)override;
	virtual void Draw(sf::RenderWindow& window)override;
};

