#include "GameSession.h"

GameSession::GameSession()
{
	// -------------------
	bg = new GameObject("../Assets/bg.png");
	bg->setPosition(CAMERA_WIDTH / 2, CAMERA_HEIGHT / 2);
	bg->scale(2.f, 2.f);
	music = new sf::Music();
	music->openFromFile("../Assets/drama.wav");
	playingMusic = false;

	// -------------------
	utils::RandSeed();
	camera = new sf::View(sf::Vector2f(CAMERA_WIDTH / 2.f, CAMERA_HEIGHT / 2.f), sf::Vector2f(CAMERA_WIDTH, CAMERA_HEIGHT));
	for (int i = 0; i < 3; i++)
		controls.push_back(new SteeringControl(new Ship()));
}

void GameSession::Update(float dt)
{
	// --- Mouse
	sf::Vector2i pixelPos = sf::Mouse::getPosition(*Window);
	Mouse->x = Window->mapPixelToCoords(pixelPos).x;
	Mouse->y = Window->mapPixelToCoords(pixelPos).y;
	// --- Boids
	for (int i = 0; i < flock.size(); i++)
	{
		flock[i]->ApplyForce(flock[i]->Seek(*Mouse));
		flock[i]->Flock(flock);
		flock[i]->Update(dt);
	}
	// --- Steering Behavior
	FunnyPart();
	for (int i = 0; i < controls.size(); i++)
		controls[i]->Update(dt);
}

void GameSession::RunEvents(sf::Event& e)
{
	switch (e.type)
	{
	case sf::Event::MouseButtonReleased:
		if (e.mouseButton.button == sf::Mouse::Button::Left)
			flock.push_back(new Ship(Mouse->x, Mouse->y));
		if (e.mouseButton.button == sf::Mouse::Button::Right)
			controls.push_back(new SteeringControl(new Ship(Mouse->x, Mouse->y)));
		break;
	}
}

void GameSession::Draw()
{
	Window->setView(*camera);
	if (playingMusic)
		Window->draw(*bg);

	// --- Draw Boids ship
	for (int i = 0; i < flock.size(); i++)
		Window->draw(*flock[i]);

	// --- Draw steeringbehavior ships
	for (int i = 0; i < controls.size(); i++)
		controls[i]->Draw();
}

void GameSession::ClearShips()
{
	for (int i = 0; i < controls.size(); i++)
		delete controls[i];
	controls.clear();
	for (int i = 0; i < flock.size(); i++)
		delete flock[i];
	flock.clear();
}

void GameSession::FunnyPart()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
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
		}
	}
}

GameSession::~GameSession()
{
	delete camera;
	ClearShips();

	delete bg;
}
