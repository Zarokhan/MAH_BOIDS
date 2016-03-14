#pragma once
#include "Window.h"

class GameObject : public sf::Sprite
{
private:
	sf::Texture texture;

public:
	GameObject(const char* path)
	{
		texture.loadFromFile(path);
		texture.setSmooth(true);
		setTexture(texture, true);

		setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	}

	virtual void Update(float dt) = 0;

	virtual ~GameObject() {}
};