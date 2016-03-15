#include "GameSession.h"

GameSession::GameSession()
{
	utils::RandSeed();
	// -------------------
	bg = new GameObject("../Assets/bg.png");
	bg->setPosition(CAMERA_WIDTH / 2, CAMERA_HEIGHT / 2);
	music = new sf::Music();
	music->openFromFile("../Assets/drama.wav");
	playingMusic = false;

	// -------------------
	camera = new sf::View(sf::Vector2f(CAMERA_WIDTH / 2.f, CAMERA_HEIGHT / 2.f), sf::Vector2f(CAMERA_WIDTH, CAMERA_HEIGHT));
	for (int i = 0; i < 3; i++)
		controls.push_back(new SteeringControl(new Ship()));
}

void GameSession::Update(float dt)
{
	sf::Vector2i pixelPos = sf::Mouse::getPosition(*Window);

	Mouse->x = Window->mapPixelToCoords(pixelPos).x;
	Mouse->y = Window->mapPixelToCoords(pixelPos).y;

	FunnyPart();

	for (int i = 0; i < controls.size(); i++)
		controls[i]->Update(dt);
}

void GameSession::Draw()
{
	Window->setView(*camera);
	if (playingMusic)
		Window->draw(*bg);

	for (int i = 0; i < controls.size(); i++)
		controls[i]->Draw();
}

void GameSession::ClearShips()
{
	for (int i = 0; i < controls.size(); i++)
		delete controls[i];

	controls.clear();
}

void GameSession::FunnyPart()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
	{
		if (!playingMusic)
		{
			playingMusic = true;
			music->play();
		}
		controls.push_back(new SteeringControl(new Ship()));
	}
	else
	{
		if (playingMusic)
		{
			music->stop();
			playingMusic = false;

			ClearShips();
			for (int i = 0; i < 3; i++)
				controls.push_back(new SteeringControl(new Ship()));
		}
	}
}

GameSession::~GameSession()
{
	delete camera;
	ClearShips();

	delete bg;
}
