#include "stdafx.h"
#include "Game.h"
#include "Shield.h"
#include "Player.h"
#include "Small.h"
#include "Medium.h"
#include "Large.h"
#include <string>


Game::Game(sf::RenderWindow * renderWindow, bool twoPlayer)
{
	window = renderWindow;
	
	//create players
	gameData[0].push_back(new Player(100, window));//player 1
	if(twoPlayer)
		gameData[0].push_back(new Player(100, window, "Player 2"));//player 2
	
	//create enemy ships
	for(int i = 0; i<11; i++)
		gameData[1].push_back(new Small(i, window));
	for (int i = 0; i < 22; i++)
	{
		gameData[1].push_back(new Medium(i, window));
		gameData[1].push_back(new Large(i, window));
	}
}


Game::~Game()
{
}


bool Game::loop()
{
	// Process events
	sf::Event event;
	while (window->pollEvent(event))
		// Close window: exit
		if (event.type == sf::Event::Closed)
			window->close();

	processKeyboard();

	//update player & check collision of bullet
	for (int i = 0; i < gameData[0].size(); i++)
	{
		Player * playerTemp = dynamic_cast<Player*> (gameData[0].at(i));
		playerTemp->update(gameData[1]);
		playerTemp->update(gameData[2]);
	}

	//test for death in ships (player & enemy)
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < gameData[i].size(); j++)
			if (dynamic_cast<Ship *>(gameData[i].at(j))->getLife() <= 0)
				gameData[i].erase(j + gameData[i].begin());

	//update text displays for player score
	for (int i = 0; i < gameData[0].size(); i++)
	{
		Player * playerTemp = dynamic_cast<Player *>(gameData[0].at(i));
	}


	if(window->isOpen() && !gameData[0].empty())
		return true;//return true while players are alive & game open
	return false;
}


void Game::render()
{
	window->clear();

	//render every index in game data
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < gameData[i].size(); j++)
			gameData[i].at(j)->render();

	window->display();
}


void Game::processKeyboard()
{
	//close window if escape pressed on keyboard
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		window->close();

	//for each player in game data
	for (int i = 0; i < gameData[0].size(); i++)
	{
		//convert from GameObject to Player
		Player * playerTemp = dynamic_cast<Player *> (gameData[0].at(i));

		//if current index is for player 1 process player 1 controls
		if (playerTemp->player == "Player 1")
		{
			//W key shoots
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				playerTemp->shoot();

			//A key move left
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				playerTemp->move(2);
			//D Key move right
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				playerTemp->move(1);
		}
		//if current index is for player 2 process player 2 controls
		else if (playerTemp->player == "Player 2")
		{
			//dpad up Shoots
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				playerTemp->shoot();

			//dpad left move left
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				playerTemp->move(2);
			//dpad right move right
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				playerTemp->move(1);
		}
	}
}