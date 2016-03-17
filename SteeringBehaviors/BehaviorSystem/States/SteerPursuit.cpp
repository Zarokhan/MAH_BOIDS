#include "SteerPursuit.h"

SteerPursuit::SteerPursuit(SteeringControl* control, char* name) : SteeringBehavior(control, name)
{
	weight = 0.5f;
}

bool SteerPursuit::Update(float dt, sf::Vector2f & totalForce)
{
	//sf::Vector2f temp = *Mouse - parent->ship->getPosition();
	//float distance = utils::VectorLenght(temp);
	//if (distance < 200)
	//	return false;

	bool adjustment = false;
	bool found = FindTarget();

	if (found)
	{
		sf::Vector2f steeringForce(0.f, 0.f);
		SteerTowards(currentTarget, steeringForce);
		totalForce += steeringForce;
		adjustment = true;
	}
	return adjustment;
}

bool SteerPursuit::FindTarget()
{
	bool retVal = false;
	// Calc mouse velocity
	sf::Vector2f mouseVel = *Mouse - beforeMouse;

	float dotVelocity = utils::Dot(parent->ship->velocity, mouseVel);
	sf::Vector2f deltaPos = *Mouse - parent->ship->getPosition();
	sf::Vector2f targetPos = *Mouse;
	if (utils::Dot(deltaPos, parent->ship->velocity) < 0 || (dotVelocity > -0.93f))
	{
		sf::Vector2f shipVel = parent->ship->velocity;
		shipVel = utils::VectorNormalize(shipVel) * parent->ship->maxSpeed;
		float combinedSpeed = utils::VectorLenght(shipVel + mouseVel);
		float predictionTime = utils::VectorLenght(deltaPos) / combinedSpeed;
		targetPos = *Mouse + (mouseVel * predictionTime);
	}

	currentTarget = targetPos;
	retVal = true;

	beforeMouse.x = Mouse->x;
	beforeMouse.y = Mouse->y;
	return retVal;
}

void SteerPursuit::Draw()
{
}