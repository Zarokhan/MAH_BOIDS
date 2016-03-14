#pragma once
#include "Window.h"
#include "Ship.h"

class GameSession
{
private:
	sf::View* camera;
	Ship* ship;
public:
	GameSession();

	void Update(float dt);
	void Draw();

	~GameSession();

	sf::Vector2f* Mouse;
};