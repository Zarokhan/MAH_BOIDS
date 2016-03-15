#pragma once
#include "SFML\Audio.hpp"
#include "Window.h"
#include "Ship.h"
#include "Utils.h"
#include "BehaviorSystem\SteeringControl.h"
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

	sf::Vector2f Separate(std::vector<SteeringControl*> boids);
	sf::Vector2f Align(std::vector<SteeringControl*> boids);
	sf::Vector2f Cohesion(std::vector<SteeringControl*> boids);

	~GameSession();

};