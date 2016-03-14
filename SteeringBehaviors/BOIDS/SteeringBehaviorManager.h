#pragma once
#include "SFML\Graphics.hpp"
#include "SteeringBehavior.h"
#include <vector>
#include <ctime>
#include <cstdlib>

class SteeringControl;

class SteeringBehaviorManager
{
public:
	SteeringBehaviorManager(SteeringControl* control = NULL);
	virtual void Update(float dt);
	virtual void AddBehaviour(SteeringBehavior* behavior);
	virtual void DisableBehavior(int index) { behaviors[index]->disable = true; }
	virtual void SetupBehavior(int behaviorIndex, float weight, float probability, bool disable = false);
	virtual void Reset();
	virtual sf::Vector2f GetFinalSteeringVector() { return totalSteeringForce; }
	virtual void Draw();
	virtual bool CombineForceWeighted(sf::Vector2f& steeringForce, float weight);
	virtual bool CombineForcePrioritySum(sf::Vector2f& steeringForce, float weight);
	virtual bool CombineForcePriorityDithered(sf::Vector2f& steeringForce, float weight, float randChance);

	inline const float randflt(int max = 1)
	{
		return static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / max));
	}

protected:
	std::vector<SteeringBehavior*> behaviors;
	std::vector<SteeringBehavior*> active;
	std::vector<float> activeForce;
	int numBehaviors;
	SteeringControl* parent;
	sf::Vector2f totalSteeringForce;
	float maxSteeringForce;
};