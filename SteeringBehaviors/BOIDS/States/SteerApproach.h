#pragma once
#include "../SteeringBehavior.h"
#include "../../Window.h"

class SteerApproach : public SteeringBehavior
{
private:
	bool FindTarget();

public:
	SteerApproach(SteeringControl* control, char* name = NULL);

	virtual bool Update(float dt, sf::Vector2f& totalForce) override;
	virtual void Draw() override;

	sf::Vector2f currentTarget;
};