#pragma once
#include "Window.h"

class GameSession
{
private:
	sf::View camera;
public:
	GameSession();

	void Update(float dt);
	void Draw();

	~GameSession();
};