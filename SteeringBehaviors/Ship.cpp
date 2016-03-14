#include "Ship.h"
#include "BOIDS\Utils.h"

Ship::Ship() : GameObject("../Assets/ship.png")
{
	maxSpeed = 10.f;
}

void Ship::Update(float dt)
{
	sf::Vector2f pos = getPosition();
	pos += velocity;
	setPosition(pos);

	//float rotation = std::atan2f(velocity.y, velocity.x);
	//setRotation(rotation * DEGREES_PER_RADIAN);
}

void Ship::ApplyForce(const sf::Vector2f & force)
{
	velocity.x = force.x;
	velocity.y = force.y;
}

Ship::~Ship()
{
}
