#include <Windows.h>
#include "Window.h"
#include "GameSession.h"

sf::RenderWindow* Window;
GameSession* Session;
sf::Vector2f* Mouse;

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
{
	Window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
	Session = new GameSession();
	Mouse = new sf::Vector2f();

	sf::Clock clock;
	sf::Time deltaTime = sf::Time::Zero;
	sf::Time ups = sf::seconds(1.f / 60.f);		// Updates per second

	// Game Loop
	while (Window->isOpen())
	{
		// Events
		sf::Event event;
		while (Window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				Window->close();
				break;
			}
		}

		while (deltaTime > ups)
		{
			deltaTime -= ups;

			Session->Update(deltaTime.asSeconds());

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
				Window->close();
		}

		Window->clear();
		Session->Draw();
		Window->display();

		deltaTime += clock.restart();
	}

	delete Session;
	delete Window;

	return EXIT_SUCCESS;
}