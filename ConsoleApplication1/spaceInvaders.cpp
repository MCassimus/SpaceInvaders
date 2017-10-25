/*
	Michael Cassimus / Daniel Barnett
	Space Invaders
	Recreate arcade game space invaders
*/
#include "stdafx.h"
#include <SFML\Graphics\RenderWindow.hpp>
#include "Game.h"
#include "GameObject.h"


int main()
{
	sf::RenderWindow window(sf::VideoMode::getFullscreenModes().at(0), "Space Invaders", sf::Style::Fullscreen);
	//sf::RenderWindow window(sf::VideoMode(620, 496, 24), "Space Invaders");
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);
	window.setMouseCursorVisible(false);

	sf::View view(sf::Rect<float>(0, 0, 310, 248));
	window.setView(view);

	GameObject menu(&window);
	menu.setTexture("mainMenu.png");
	menu.setPosition(sf::Vector2f(window.getView().getSize().x / 2, window.getView().getSize().y / 2));

	Game * game = nullptr;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::Resized)
			{
				double ratio = event.size.width / view.getSize().x;
				view.setCenter(view.getSize().x / 2, view.getSize().y / 2);
				sf::VideoMode vidModeTemp(view.getSize().x, view.getSize().y, 24);
				window.close();
				window.create(vidModeTemp, "Space Invaders", sf::Style::Fullscreen);
				window.setView(view);
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Num1 && game == nullptr)
					game = new Game(&window, false);
				else if (event.key.code == sf::Keyboard::Num2 && game == nullptr)
					game = new Game(&window, true);
				else if (event.key.code == sf::Keyboard::Escape)
					window.close();
			}

			if (game != nullptr)
			{
				while (game->loop())
					game->render();
				
				delete game;
				game = nullptr;
			}
		}

		window.clear();
		menu.render();
		window.display();
	}
	
	return 0;
}