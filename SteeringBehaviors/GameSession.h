#pragma once
#include "SFML\Audio.hpp"
#include "Window.h"
#include "Ship.h"
#include "BOIDS\SteeringControl.h"
#include <vector>

class GameSession
{
private:
	sf::View* camera;
	std::vector<SteeringControl*> controls;

	sf::Music* music;
	bool playingMusic;
	GameObject* bg;
public:
	GameSession();

	void Update(float dt);
	void Draw();
	void ClearShips();
	void FunnyPart();

	~GameSession();

};