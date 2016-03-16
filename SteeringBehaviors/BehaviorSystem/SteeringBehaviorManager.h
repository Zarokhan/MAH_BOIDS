#pragma once
#include "SFML\Graphics.hpp"
#include "../utils.h"
#include "SteeringBehavior.h"
#include <vector>

class SteeringControl;

class SteeringBehaviorManager
{
protected:
	std::vector<SteeringBehavior*> behaviors;
	std::vector<SteeringBehavior*> active;
	std::vector<float> activeForce;
	int numBehaviors;
	SteeringControl* parent;
	sf::Vector2f totalSteeringForce;
	float maxSteeringForce;

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

	~SteeringBehaviorManager();
};