#include "stdafx.h"
#include "Game.h"
#include "Shield.h"
#include "Player.h"
#include "Small.h"
#include "Medium.h"
#include "Large.h"
#include <string>
#include <iostream>
#include "Word.h"


Game::Game(sf::RenderWindow * renderWindow, bool twoPlayer)
{
	window = renderWindow;
	
	#pragma region createObjects
	//create players
	gameData[0].push_back(new Player(8, window));//player 1
	if(twoPlayer)
		gameData[0].push_back(new Player(window->getView().getSize().x - 8, window, "Player 2"));//player 2

	lifeSeperator = sf::RectangleShape(sf::Vector2f(9999999, 1));
	lifeSeperator.setPosition(sf::Vector2f(0, window->getView().getSize().y - 16));
	
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

	//ititalize sounds for enemy movement
	sounds.loadFromFile("../Sounds/EnemyMove/enemyMove1.wav");
	enemyMoveSound.setBuffer(sounds);

	srand(time(NULL));

	level = 1;
}


Game::~Game()
{
}


bool Game::loop()
{
	static int ticks = 0;
	ticks++;

	static int endticks = -10000;
	
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				if (pause)
					pause = false;
				else
					pause = true;
			}
			else if (event.key.code == sf::Keyboard::BackSpace && pause)
				return false;
		}
		// Close window: exit
		else if (event.type == sf::Event::Closed)
			window->close();
	}

	if (!pause)
	{
		//process events
		processKeyboard();

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
		//enemy movement & sound
		if (ticks % 20 == 0 &&ticks>endticks+100)
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

			static int sound = 0;
			switch (sound)
			{
			case 0:
				sounds.loadFromFile("../Sounds/EnemyMove/enemyMove1.wav");
				sound++;
				break;
			case 1:
				sounds.loadFromFile("../Sounds/EnemyMove/enemyMove2.wav");
				sound++;
				break;
			case 2:
				sounds.loadFromFile("../Sounds/EnemyMove/enemyMove3.wav");
				sound++;
				break;
			case 3:
				sounds.loadFromFile("../Sounds/EnemyMove/enemyMove4.wav");
				sound = 0;
				break;
			}
			enemyMoveSound.play();
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

		//check player death
		for (int i = 0; i < gameData[0].size(); i++)
			if (dynamic_cast<Player *>(gameData[0].at(i))->getLife() == 0)
				gameData[0].erase(gameData[0].begin() + i);

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

		//check if no more enemies, then displays next level
		if (ticks > endticks + 100)
		{
			int i = 0;
			while (i < gameData[1].size() && dynamic_cast<Ship*>(gameData[1].at(i))->getLife() == 0)
			{
				i++;
			}
			if (i == gameData[1].size())
			{
				level++;
				endticks = ticks;
				gameData[3].push_back(new Word(window, "LEVEL " + std::to_string(level)));
				sf::Vector2f oldsize(window->getView().getSize());
				gameData[3].back()->setPosition(sf::Vector2f(oldsize.x,(3*oldsize.y)/4));
				gameData[3].back()->setFillColor(sf::Color::White);
				gameData[3].back()->update();
			}
		}

		if (ticks == endticks + 100)
		{
			gameData[3].pop_back();
			for (int j = 0; j < gameData[1].size(); j++)
			{
				delete gameData[1].at(j);
			}
			gameData[1].clear();

			for (int j = 0; j < gameData[2].size(); j++)
			{
				delete gameData[2].at(j);
			}
			gameData[2].clear();

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

			for (int i = 0; i < 4; i++)
				gameData[2].push_back(new Shield(i, window));
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
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < gameData[i].size(); j++)
			gameData[i].at(j)->render();

	window->draw(lifeSeperator);

	window->display();
}


void Game::processKeyboard()
{


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

			//E key cheat code
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
			{
				int i = 0;
				while (i < gameData[1].size() && dynamic_cast<Ship*>(gameData[1].at(i))->getLife() == 0)
				{
					i++;
				}

				if (i < gameData[1].size())
				{
					dynamic_cast<Ship*>(gameData[1].at(i))->takeLife();
				}
				
			}
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