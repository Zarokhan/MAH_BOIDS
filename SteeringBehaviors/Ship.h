#pragma once
#include "GameObject.h"

class Ship : public GameObject
{
public:
	Ship();
	~Ship();

	virtual void Update(float dt) override;

	sf::Vector2f velocity;
	float maxSpeed;
};