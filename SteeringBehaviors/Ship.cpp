#include "Ship.h"
#include "Utils.h"

void Ship::init()
{
	maxSpeed = 5.f;
	maxForce = 0.03f;
}

void Ship::Update(float dt)
{
	velocity += acceleration;
	velocity.x = MIN(velocity.x, maxSpeed);
	velocity.x = MAX(velocity.x, -maxSpeed);
	velocity.y = MIN(velocity.y, maxSpeed);
	velocity.y = MAX(velocity.y, -maxSpeed);

	setPosition(getPosition() + velocity);

	acceleration.x = 0;
	acceleration.y = 0;

	//sf::Vector2f pos = getPosition();
	//pos += velocity;
	//setPosition(pos);

	//float rotation = std::atan2f(velocity.y, velocity.x);
	//setRotation(rotation * DEGREES_PER_RADIAN);
}

void Ship::ApplyForce(const sf::Vector2f &force)
{
	acceleration += force;
}

void Ship::Flock(const std::vector<Ship*> &boids)
{
	sf::Vector2f sep = Separate(boids);
	sf::Vector2f ali = Align(boids);
	sf::Vector2f coh = Cohesion(boids);
	// Adjust values (weight)
	sep *= 1.f;
	ali *= 1.f;
	coh *= 1.f;
	// Add force vectors to acceleration
	ApplyForce(sep);
	ApplyForce(ali);
	ApplyForce(coh);
}

sf::Vector2f Ship::Seek(const sf::Vector2f &target)
{
	sf::Vector2f desired = target - getPosition();
	desired = utils::VectorNormalize(desired);
	desired *= maxSpeed;

	sf::Vector2f steer = desired - velocity;
	steer.x = MIN(steer.x, maxForce);
	steer.x = MAX(steer.x, -maxForce);
	steer.y = MIN(steer.y, maxForce);
	steer.y = MAX(steer.y, -maxForce);

	return steer;
}

sf::Vector2f Ship::Separate(const std::vector<Ship*> &boids)
{
	float desiredseparation = 25.f;
	sf::Vector2f steer;
	
	for (int i = 0; i < boids.size(); i++)
	{

	}

	return sf::Vector2f();
}

sf::Vector2f Ship::Align(const std::vector<Ship*> &boids)
{
	return sf::Vector2f();
}

sf::Vector2f Ship::Cohesion(const std::vector<Ship*> &boids)
{
	return sf::Vector2f();
}

Ship::~Ship()
{
}
