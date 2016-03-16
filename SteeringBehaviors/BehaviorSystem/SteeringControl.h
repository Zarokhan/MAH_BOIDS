#pragma once
#include "../Ship.h"

class SteeringBehaviorManager;

class SteeringControl
{
public:
	Ship* ship;

public:
	SteeringControl(Ship* ship) : ship(ship) { Init(); }
	
	void Update(float dt);
	void UpdatePerceptions(float dt);
	void Init();
	void Draw();
	void Reset();

	~SteeringControl();
protected:
	SteeringBehaviorManager* manager;
};