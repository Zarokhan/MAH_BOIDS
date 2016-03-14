#include "GameSession.h"

GameSession::GameSession()
{
	camera = new sf::View(sf::Vector2f(CAMERA_WIDTH / 2.f, CAMERA_HEIGHT / 2.f), sf::Vector2f(CAMERA_WIDTH, CAMERA_HEIGHT));
	ship = new Ship();
	Mouse = new sf::Vector2f();
}

void GameSession::Update(float dt)
{
	sf::Vector2i pixelPos = sf::Mouse::getPosition(*Window);

	Mouse->x = Window->mapPixelToCoords(pixelPos).x;
	Mouse->y = Window->mapPixelToCoords(pixelPos).y;

}

void GameSession::Draw()
{
	Window->setView(*camera);
	Window->draw(*ship);
}

GameSession::~GameSession()
{
	delete camera;
	delete ship;
}
