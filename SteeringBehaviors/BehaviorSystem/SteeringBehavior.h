#pragma once
#include "SteeringControl.h"
#include "../Utils.h"

class SteeringBehavior
{
public:
	SteeringBehavior(SteeringControl* control, char* name = NULL) : parent(control)
	{
		//memcpy(this->name, name, strlen(name) + 1);
		disable = false;
		lastForceMagApplied = 0.f;
	}

	virtual bool Update(float dt, sf::Vector2f& totalForce) { return false; }
	virtual void Reset() {}
	virtual void Draw() {}

	virtual void SteerTowards(sf::Vector2f& target, sf::Vector2f& result)
	{
		sf::Vector2f desired = target - parent->ship->getPosition();
		float targetDistance = utils::VectorLenght(desired);
		if (targetDistance > 0)
		{
			desired = utils::VectorNormalize(desired) * parent->ship->maxSpeed;
			result = desired - parent->ship->velocity;
		}
		else
			result = sf::Vector2f();
	}

	virtual void SteerAway(sf::Vector2f& target, sf::Vector2f& result)
	{
		sf::Vector2f desired = parent->ship->getPosition() - target;
		float targetDistance = utils::VectorLenght(desired);
		if (targetDistance > 0)
		{
			desired = utils::VectorNormalize(desired) * parent->ship->maxSpeed;
			result = desired - parent->ship->velocity;
		}
		else
			result = sf::Vector2f();
	}

	SteeringControl* parent;
	float weight;
	float propbability;
	char name[30];
	bool disable;
	float lastForceMagApplied;
};