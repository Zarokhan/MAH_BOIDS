#include "SteeringControl.h"
#include "SteeringBehaviorManager.h"
#include "States\SteerApproach.h"
#include "States\SteerWander.h"
#include "States\SteerArrive.h"

void SteeringControl::Init()
{
	manager = new SteeringBehaviorManager(this);
	manager->AddBehaviour(new SteerApproach(this));
	manager->AddBehaviour(new SteerWander(this));
	manager->AddBehaviour(new SteerArrive(this));
}

void SteeringControl::Update(float dt)
{
	if (!ship)
	{
		manager->Reset();
		return;
	}

	UpdatePerceptions(dt);
	manager->Update(dt);
	sf::Vector2f totalSteeringForce = manager->GetFinalSteeringVector();
	ship->Update(dt);
	ship->ApplyForce(totalSteeringForce);
}

void SteeringControl::UpdatePerceptions(float dt)
{
}

void SteeringControl::Draw()
{
	Window->draw(*ship);
}

void SteeringControl::Reset()
{
}

SteeringControl::~SteeringControl()
{
	delete ship;
}
