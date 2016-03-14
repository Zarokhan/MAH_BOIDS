#include "SteerApproach.h"

SteerApproach::SteerApproach(SteeringControl* control, char* name) : SteeringBehavior(control, name)
{
}

bool SteerApproach::Update(float dt, sf::Vector2f & totalForce)
{
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

	return retVal;
}

void SteerApproach::Draw()
{
}
