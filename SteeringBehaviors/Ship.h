#pragma once
#include "GameObject.h"

class Ship : public GameObject
{
public:
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	float r;
	float maxSpeed;
	float maxForce;

	Ship(int x = 0, int y = 0) : GameObject("../Assets/ship.png") { setPosition(x, y); init(); }
	~Ship();

	void init();
	void ApplyForce(const sf::Vector2f& force);
	void Flock(const std::vector<Ship*>& boids);
	sf::Vector2f Seek(const sf::Vector2f& target);
	sf::Vector2f Separate(const std::vector<Ship*>& boids);
	sf::Vector2f Align(const std::vector<Ship*>& boids);
	sf::Vector2f Cohesion(const std::vector<Ship*>& boids);
	virtual void Update(float dt) override;
};