#include "stdafx.h"
#include "Game.h"
#include "Shield.h"
#include "Player.h"
#include "Small.h"
#include "Medium.h"
#include "Large.h"
#include <iostream>


Game::Game(sf::RenderWindow * renderWindow, bool twoPlayer)
{
	window = renderWindow;
	gameData[0].push_back(new Player(100, window));
	if(twoPlayer)
		gameData[0].push_back(new Player(100, window, "Player 2"));
	gameData[1].push_back(new Small(25, window));
	gameData[1].push_back(new Medium(100, window));
	gameData[1].push_back(new Large(175, window));

}


Game::~Game()
{
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

	
	if(window->isOpen() && !gameData[0].empty())
		return true;//return true while players are alive & game open
	return false;
}


void Game::render()
{
	window->clear();

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < gameData[i].size(); j++)
			gameData[i].at(j)->render();

	window->display();
}


void Game::processKeyboard()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		window->close();


	for (int i = 0; i < gameData[0].size(); i++)
	{
		Player * playerTemp = dynamic_cast<Player *> (gameData[0].at(i));

		if (playerTemp->player == "Player 1")
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				std::cout << "Player 1 - FIRE\n";
				playerTemp->shoot();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))

				playerTemp->move(false);
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				playerTemp->move(true);
		}
		else if (playerTemp->player == "Player 2")
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				std::cout << "Player 2 - FIRE\n";
				playerTemp->shoot();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				playerTemp->move(false);
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				playerTemp->move(true);
		}
	}
}