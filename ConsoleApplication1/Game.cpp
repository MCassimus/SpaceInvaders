#include "stdafx.h"
#include "Game.h"
#include "Shield.h"
#include "Player.h"
#include "Small.h"
#include "Medium.h"
#include "Large.h"
#include <string>
#include <iostream>


Game::Game(sf::RenderWindow * renderWindow, bool twoPlayer)
{
	window = renderWindow;
	
	#pragma region createObjects
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
	}
	for (int i = 0; i < 22; i++)
	{
		gameData[1].push_back(new Large(i, window));
	}

	//create shields
	for (int i = 0; i < 4; i++)
		gameData[2].push_back(new Shield(i , window));
	#pragma endregion

	srand(time(NULL));
}


Game::~Game()
{
}


bool Game::loop()
{
	static int ticks = 0;
	ticks++;

	#pragma region eventProcessing
	// Process events
	sf::Event event;
	while (window->pollEvent(event))
		// Close window: exit
		if (event.type == sf::Event::Closed)
			window->close();

	processKeyboard();
	#pragma endregion

	#pragma region updateObjects
	//update player
	for (int i = 0; i < gameData[0].size(); i++)
	{
		Player * playerTemp = dynamic_cast<Player*> (gameData[0].at(i));
		playerTemp->update(gameData[1]);//update with enemy param
		playerTemp->update(gameData[2]);//update with shile param
	}

	//update enemy
	for (int i = 0; i < gameData[1].size(); i++)
	{
		Ship * shipTemp = dynamic_cast<Ship*> (gameData[1].at(i));
		shipTemp->update(gameData[0]);//update with player param
		shipTemp->update(gameData[2]);//update with shield param
	}

	//update shield
	for (int i = 0; i < gameData[2].size(); i++)
	{
		Shield * shieldTemp = dynamic_cast<Shield *>(gameData[2].at(i));
		shieldTemp->update();
		if (shieldTemp->getHealth() <= 0)//if shield is dead
			gameData[2].erase(gameData[2].begin() + i);//remove from vector
	}
	#pragma endregion

	#pragma region enemyMovement
	//enemy movement
	if (ticks % 20 == 0)
	{
		static int dir = 1;
		if (dir == 0 || dir == 3)
		{
			for (int i = 0; i < gameData[1].size(); i++)
				dynamic_cast<Ship*>(gameData[1].at(i))->move(0);
			if (dir == 0)
				dir = 2;
			else
				dir = 1;
		}
		else if (dir == 1)
		{
			for (int i = 0; i < gameData[1].size(); i++)
				if (dynamic_cast<Ship*>(gameData[1].at(i))->move(1))
					dir = 0;
		}
		else
		{
			for (int i = 0; i < gameData[1].size(); i++)
				if (dynamic_cast<Ship*>(gameData[1].at(i))->move(2))
					dir = 3;
		}
	}

	//update enemy texture
	for (int i = 0; i < gameData[1].size(); i++)
	{
		if (ticks % 40 == 0)
		{
			std::string type = typeid(*gameData[1].at(i)).name();

			if (type == "class Small")
				gameData[1].at(i)->setTexture("smallShip0.png");
			else if (type == "class Medium")
				gameData[1].at(i)->setTexture("mediumShip0.png");
			else if (type == "class Large")
				gameData[1].at(i)->setTexture("largeShip0.png");
		}
		else if(ticks % 20 == 0)
		{
			std::string type = typeid(*gameData[1].at(i)).name();

			if (type == "class Small")
				gameData[1].at(i)->setTexture("smallShip1.png");
			else if (type == "class Medium")
				gameData[1].at(i)->setTexture("mediumShip1.png");
			else if (type == "class Large")
				gameData[1].at(i)->setTexture("largeShip1.png");
		}
	}
	#pragma endregion 

	//random enemy shooting
	for (int i = 0; i < 11; i++)
	{
		if (rand() % 200 == 0)
		{
			int j = 44 + i;
			while (j >= 0 && !dynamic_cast<Ship*>(gameData[1].at(j))->shoot())
			{
				j -= 11;
			}
		}
	}

	//check if no more enemies
	int i = 0;
	while (i < gameData[1].size() && dynamic_cast<Ship*>(gameData[1].at(i))->getLife()==0)
	{
		i++;
	}
	if (i == gameData[1].size())
	{
		for (int j = 0; j < gameData[1].size(); j++)
		{
			delete gameData[1].at(j);
		}
		gameData[1].clear();


		for (int j = 0; j<11; j++)
			gameData[1].push_back(new Small(j, window));
		for (int j = 0; j < 22; j++)
		{
			gameData[1].push_back(new Medium(j, window));
		}
		for (int j = 0; j < 22; j++)
		{
			gameData[1].push_back(new Large(j, window));
		}
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