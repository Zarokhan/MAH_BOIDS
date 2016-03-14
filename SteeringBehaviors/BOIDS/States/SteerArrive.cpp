#include "SteerArrive.h"

SteerArrive::SteerArrive(SteeringControl * control, char * name) : SteeringBehavior(control, name)
{
	weight = 0.3f;
}

#define AI_MAX_SPEED_TRY 10
bool SteerArrive::Update(float dt, sf::Vector2f & totalForce)
{
	bool adjustment = false;

	currentTarget.x = Mouse->x;
	currentTarget.y = Mouse->y;

	sf::Vector2f targetDelta = currentTarget - parent->ship->getPosition();
	float distToTarget = utils::VectorLenght(targetDelta);
	if (distToTarget > 0)
	{
		float speed = parent->ship->maxSpeed * (distToTarget / AI_MAX_SPEED_TRY);
		speed = MIN(speed, parent->ship->maxSpeed);
		targetDelta = utils::VectorNormalize(targetDelta);
		targetDelta *= speed;
		totalForce += targetDelta - parent->ship->velocity;
		adjustment = true;
	}

	return adjustment;
}

void SteerArrive::Draw()
{
}
