#include "Ship.h"
#include "Utils.h"

void Ship::init()
{
	maxSpeed = 5.f;
	maxForce = 3.f;
	
	float angle = utils::randflt(PI * 2);
	velocity.x = std::cosf(angle);
	velocity.y = std::sinf(angle);
	r = 2.f;
}

void Ship::Update(float dt)
{
	velocity += acceleration;
	//velocity.x = MIN(velocity.x, maxSpeed);
	//velocity.x = MAX(velocity.x, -maxSpeed);
	//velocity.y = MIN(velocity.y, maxSpeed);
	//velocity.y = MAX(velocity.y, -maxSpeed);

	setPosition(getPosition() + velocity);

	acceleration.x = 0;
	acceleration.y = 0;

	// ---- Rotation
	float rotation = std::atan2f(velocity.y, velocity.x);
	setRotation(rotation * DEGREES_PER_RADIAN);
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
	coh *= 0.75f;
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
	//steer.x = MIN(steer.x, maxForce);
	//steer.x = MAX(steer.x, -maxForce);
	//steer.y = MIN(steer.y, maxForce);
	//steer.y = MAX(steer.y, -maxForce);

	return steer;
}

sf::Vector2f Ship::Separate(const std::vector<Ship*> &boids)
{
	float desiredseparation = 50.f;
	sf::Vector2f steer;
	
	int count = 0;
	for (int i = 0; i < boids.size(); i++)
	{
		float d = utils::Distance(getPosition(), boids[i]->getPosition());
		if ((d > 0) && (d < desiredseparation))
		{
			sf::Vector2f diff = getPosition() - boids[i]->getPosition();
			diff = utils::VectorNormalize(diff);
			diff /= d;
			steer += diff;
			count++;
		}
	}

	// Avrage
	if (count > 0)
		steer /= (float)count;

	if (utils::VectorLenght(steer) > 0)
	{
		steer = utils::VectorNormalize(steer);
		steer *= maxSpeed;
		steer -= velocity;
		//steer.x = MIN(steer.x, maxForce);
		//steer.x = MAX(steer.x, -maxForce);
		//steer.y = MIN(steer.y, maxForce);
		//steer.y = MAX(steer.y, -maxForce);
	}

	return steer;
}

sf::Vector2f Ship::Align(const std::vector<Ship*> &boids)
{
	float neighbordist = 75.f;
	sf::Vector2f sum;
	int count = 0;
	for (int i = 0; i < boids.size(); i++)
	{
		float d = utils::Distance(getPosition(), boids[i]->getPosition());
		if ((d > 0) && (d < neighbordist))
		{
			sum += boids[i]->velocity;
			count++;
		}
	}

	if (count > 0)
	{
		sum /= (float)count;
		sum = utils::VectorNormalize(sum);
		sum *= maxSpeed;
		sf::Vector2f steer = sum - velocity;
		//steer.x = MIN(steer.x, maxForce);
		//steer.x = MAX(steer.x, -maxForce);
		//steer.y = MIN(steer.y, maxForce);
		//steer.y = MAX(steer.y, -maxForce);
		return steer;
	}
	return sf::Vector2f();
}

sf::Vector2f Ship::Cohesion(const std::vector<Ship*> &boids)
{
	float neightbordist = 75.f;
	sf::Vector2f sum;
	int count = 0;
	for (int i = 0; i < boids.size(); i++)
	{
		float d = utils::Distance(getPosition(), boids[i]->getPosition());
		if ((d > 0) && (d < neightbordist))
		{
			sum += boids[i]->getPosition();
			count++;
		}
	}
	if (count > 0)
	{
		sum /= (float)count;
		return Seek(sum);
	}
	return sf::Vector2f();
}

Ship::~Ship()
{

}
