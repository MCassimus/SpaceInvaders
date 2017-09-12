#include "stdafx.h"
#include "Game.h"
#include "Shield.h"
#include <iostream>


Game::Game(sf::RenderWindow * renderWindow)
{
	window = renderWindow;
}


Game::~Game()
{
	delete shield;
}


bool Game::loop()
{
	// Process events
	sf::Event event;
	while (window->pollEvent(event))
	{
		// Close window: exit
		if (event.type == sf::Event::Closed)
			window->close();
	}

	processKeyboard();

	
	if(window->isOpen()/* && player1 != nullptr || player2 != nullptr*/ )
		return true;//return true while players are alive & game open
	return false;
}


void Game::render()
{
	window->clear();

	window->display();
}


void Game::processKeyboard()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		window->close();

	//if (player1 != nullptr)
	//{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			//std::cout << "Player 1  - MOVE LEFT\n";
			//player1.move(false);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			//std::cout << "Player 1 - MOVE RIGHT\n";
			//player1.move(true);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			//std::cout << "Player 1 - FIRE\n";
			//player1.shoot();
		}
	//}
	

	//if (player2 != nullptr)
	//{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			std::cout << "Player 2  - MOVE LEFT\n";
		//player2.move(false);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			std::cout << "Player 2 - MOVE RIGHT\n";
		//player2.move(true);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			std::cout << "Player 2 - FIRE\n";
		//player2.shoot();
	//}
}