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
	sf::View* camera;						// Camera view
	std::vector<SteeringControl*> controls;	// Ships for steering behavior
	std::vector<Ship*> flock;				// Ships for flocking

	// ---- Funny part
	sf::Music* music;
	bool playingMusic;
	GameObject* bg;
	void FunnyPart();
public:
	GameSession();

	void Update(float dt);
	void RunEvents(sf::Event& e);
	void Draw();
	void ClearShips();

	~GameSession();
};