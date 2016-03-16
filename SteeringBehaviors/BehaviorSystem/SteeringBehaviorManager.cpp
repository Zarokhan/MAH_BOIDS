#include "SteeringBehaviorManager.h"

SteeringBehaviorManager::SteeringBehaviorManager(SteeringControl * control)
{
	this->parent = control;
	maxSteeringForce = 100;
}

void SteeringBehaviorManager::Update(float dt)
{
	// Don't do anything if you have no states
	if (behaviors.size() == 0)
		return;

	// Clear out debug logs
	active.clear();
	activeForce.clear();

	// Reset the steering vector
	totalSteeringForce = sf::Vector2f();

	// Update all the behaviors
	bool needToClamp = false;
	for (unsigned int i = 0; i < behaviors.size(); i++)
	{
		sf::Vector2f steeringForce(0.f, 0.f);
		bool didSomething = behaviors[i]->Update(dt, steeringForce);
		
		if (didSomething)
		{
			// Keep track of the behaviors that actually did something this tick
			active.push_back(behaviors[i]);
			activeForce.push_back(utils::VectorLenght(steeringForce));

			// Now we want combine the behaviors into the totalt steering force using whatever method we decide upon
			bool keepGoing = CombineForceWeighted(steeringForce, behaviors[i]->weight);
			needToClamp = true;

			if (!keepGoing)
				return;
		}
	}

	if (needToClamp)
		utils::CLAMPVECTORLENGTH(totalSteeringForce, 0.f, maxSteeringForce);
}

void SteeringBehaviorManager::AddBehaviour(SteeringBehavior* behavior)
{
	behaviors.push_back(behavior);
}

void SteeringBehaviorManager::SetupBehavior(int behaviorIndex, float weight, float probability, bool disable)
{
}

void SteeringBehaviorManager::Reset()
{
}

void SteeringBehaviorManager::Draw()
{
}

bool SteeringBehaviorManager::CombineForceWeighted(sf::Vector2f & steeringForce, float weight)
{
	totalSteeringForce += steeringForce * weight;
	return true;
}

bool SteeringBehaviorManager::CombineForcePrioritySum(sf::Vector2f & steeringForce, float weight)
{
	bool retVal = false;

	float totalForce = utils::VectorLenght(totalSteeringForce);
	float forceLeft = maxSteeringForce - totalForce;
	if (forceLeft > 0.f)
	{
		float newForce = utils::VectorLenght(steeringForce);
		if (newForce < forceLeft)
			totalSteeringForce += steeringForce;
		else
			totalSteeringForce += utils::VectorNormalize(totalSteeringForce) * forceLeft;

		if ((forceLeft - newForce) > 0)
			retVal = true;
	}

	return retVal;
}

bool SteeringBehaviorManager::CombineForcePriorityDithered(sf::Vector2f & steeringForce, float weight, float randChance)
{
	bool retVal = true;
	if (utils::randflt() < randChance)
	{
		if (utils::VectorLenght(steeringForce))
		{
			totalSteeringForce = steeringForce;
			retVal = false;
		}
	}

	return retVal;
}

SteeringBehaviorManager::~SteeringBehaviorManager()
{
	for (auto i = 0; i < behaviors.size(); i++)
		delete behaviors[i];
	behaviors.clear();
	for (auto i = 0; i < active.size(); i++)
		delete active[i];
	active.clear();
}
