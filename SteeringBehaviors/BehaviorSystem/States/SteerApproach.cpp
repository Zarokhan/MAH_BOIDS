#include "SteerApproach.h"

SteerApproach::SteerApproach(SteeringControl* control, char* name) : SteeringBehavior(control, name)
{
	weight = 0.5f;
}

bool SteerApproach::Update(float dt, sf::Vector2f & totalForce)
{
	sf::Vector2f temp = *Mouse - parent->ship->getPosition();
	float distance = utils::VectorLenght(temp);
	if (distance < 200)
		return false;

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

bool SteerApproach::FindTarget()
{
	bool retVal = false;

	if (Mouse)
	{
		currentTarget.x = Mouse->x;
		currentTarget.y = Mouse->y;
		retVal = true;
	}

	return retVal;
}

void SteerApproach::Draw()
{
}
