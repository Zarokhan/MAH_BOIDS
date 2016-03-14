#include "SteerWander.h"

SteerWander::SteerWander(SteeringControl * control, char * name) : SteeringBehavior(control, name)
{
	weight = 0.3f;
	wanderCircleDistance = 500.f;
	wanderCircleRadius = 500.f;
}

bool SteerWander::Update(float dt, sf::Vector2f & totalForce)
{
	bool adjustment = false;

	sf::Vector2f steeringForce;

	float delta = 0.15f;
	thetaValue += (randflt() * 2 * delta) - delta;

	circlePosition = parent->ship->velocity;
	circlePosition = utils::VectorNormalize(circlePosition);
	circlePosition *= wanderCircleDistance;
	circlePosition += parent->ship->getPosition();
	sf::Vector2f circleTarget(wanderCircleRadius*std::cos(thetaValue), wanderCircleRadius*std::sin(thetaValue));
	sf::Vector2f target = circlePosition + circleTarget;
	SteerTowards(target, steeringForce);

	float distanceToObject = utils::VectorLenght(steeringForce);
	if (distanceToObject)
	{
		totalForce += steeringForce;
		adjustment = true;
		targetPosition = target;
	}

	return adjustment;
}

void SteerWander::Draw()
{
}
