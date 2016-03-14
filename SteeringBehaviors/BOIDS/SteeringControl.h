#pragma once
#include "../Ship.h"
#include "SteeringBehaviorManager.h"

class SteeringControl
{
public:
	SteeringControl(Ship* ship) : ship(ship) { Init(); }
	
	void Update(float dt);
	void UpdatePerceptions(float dt);
	void Init();
	void Draw();
	void Reset();

	Ship* ship;
protected:
	SteeringBehaviorManager* behaviorManager;

};