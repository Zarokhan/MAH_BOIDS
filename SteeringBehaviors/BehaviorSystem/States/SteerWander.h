#pragma once
#include "../SteeringBehavior.h"
#include "../../Window.h"

class SteerWander : public SteeringBehavior
{
public:
	SteerWander(SteeringControl* control, char* name = NULL);

	virtual bool Update(float dt, sf::Vector2f& totalForce) override;
	virtual void Draw() override;

	inline const float randflt(int max = 1)
	{
		return static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / max));
	}

	float thetaValue;
	float wanderCircleDistance;
	float wanderCircleRadius;
	sf::Vector2f circlePosition;
	sf::Vector2f targetPosition;
};