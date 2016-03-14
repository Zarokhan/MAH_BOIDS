#include "SteeringControl.h"

void SteeringControl::Init()
{
	behaviorManager = new SteeringBehaviorManager(this);
}

void SteeringControl::Update(float dt)
{
}

void SteeringControl::UpdatePerceptions(float dt)
{
}

void SteeringControl::Draw()
{
}

void SteeringControl::Reset()
{
}
