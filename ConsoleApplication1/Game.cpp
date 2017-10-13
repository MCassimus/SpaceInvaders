#include "stdafx.h"
#include <string>
#include "Game.h"
#include "Shield.h"
#include "Player.h"
#include "Small.h"
#include "Medium.h"
#include "Large.h"
#include "UFO.h"
#include "Word.h"
#include <iostream>


Game::Game(sf::RenderWindow * renderWindow, bool twoPlayer)
{
	window = renderWindow;
	
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
		gameData[1].push_back(new Medium(i, window));
	for (int i = 0; i < 22; i++)
		gameData[1].push_back(new Large(i, window));



	Ship * ufo = new UFO(window);
	ufo->takeLife();
	ufo->update();
	gameData[1].push_back(ufo);

	//create shields
	for (int i = 0; i < 4; i++)
		gameData[2].push_back(new Shield(i , window));

	gameData[3].push_back(new Word(window, "", 12));

	//ititalize sounds for enemy movement
	sounds.loadFromFile("Sounds/EnemyMove/enemyMove1.wav");
	soundPlayer.setBuffer(sounds);

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
			if (event.key.code == sf::Keyboard::Escape)
			{
				if (pause)
					pause = false;
				else
					pause = true;
			}
			else if (event.key.code == sf::Keyboard::BackSpace && pause)
				return false;
		if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			playerShoot(event);
		// Close window: exit
		else if (event.type == sf::Event::Closed)
			window->close();
	}

	if (!pause)
	{
		//process events
		processKeyboard();

		//update player
		for (int i = 0; i < gameData[0].size(); i++)
		{
			Player * playerTemp = dynamic_cast<Player*> (gameData[0].at(i));
			playerTemp->update(gameData[1]);//update with enemy param
			playerTemp->update(gameData[2]);//update with shield param
		}

		int liveEnemies = 0;
		//update enemy
		for (int i = 0; i < gameData[1].size(); i++)
		{
			Ship * shipTemp = dynamic_cast<Ship*> (gameData[1].at(i));
			if (shipTemp != nullptr)
			{
				liveEnemies++;
				shipTemp->update(gameData[0]);//update with player param
				shipTemp->update(gameData[2]);//update with shield param
				if (shipTemp->getLife() == 0)
				{
					std::vector<std::string> frameFiles;
					frameFiles.push_back("transparent.png");
					gameData[1].at(i) = new Animation(shipTemp->getPosition(), frameFiles, window);
				}

				//update ufo
				if (i == 55)
					shipTemp->update();
			}
			else
			{
				//update animations
				Animation * animationTemp = dynamic_cast<Animation*>(gameData[1].at(i));
				animationTemp->update();
			}
		}

		//update shield
		for (int i = 0; i < gameData[2].size(); i++)
		{
			Shield * shieldTemp = dynamic_cast<Shield *>(gameData[2].at(i));
			shieldTemp->update();
			if (shieldTemp->getHealth() <= 0)//if shield is dead
				gameData[2].erase(gameData[2].begin() + i);//remove from vector
		}

		//update the score display
		std::string player1Score = "0", player2Score = "0";
		for (int i = 0; i < gameData[0].size(); i++)
		{
			if (dynamic_cast<Player *>(gameData[0].at(i))->player == "Player 1")
				player1Score = std::to_string(dynamic_cast<Player *>(gameData[0].at(i))->getScore());
			else
				player2Score = std::to_string(dynamic_cast<Player *>(gameData[0].at(i))->getScore());
		}

		while (player1Score.length() < 5)
			player1Score = "0" + player1Score;

		while (player2Score.length() < 5)
			player2Score = "0" + player2Score;

		sf::Vector2f oldsize(window->getView().getSize());
		gameData[3].front()->setTexture("SCORE <1>  " + player1Score + "                                " + player2Score + "  SCORE <2>");
		gameData[3].front()->setPosition(sf::Vector2f(oldsize.x, 16));
		gameData[3].front()->update();

		static int difficulty = 40;

		static int dir = 1;
		//enemy movement & sound

		if (ticks > endticks + 100)
		{
		if (ticks % difficulty == 0 && ticks > endticks + 100 && liveEnemies > 0)
		{
			static int sound = 0;
			switch (sound)
			{
			case 0:
				sounds.loadFromFile("Sounds/EnemyMove/enemyMove1.wav");
				sound++;
				break;
			case 1:
				sounds.loadFromFile("Sounds/EnemyMove/enemyMove2.wav");
				sound++;
				break;
			case 2:
				sounds.loadFromFile("Sounds/EnemyMove/enemyMove3.wav");
				sound++;
				break;
			case 3:
				sounds.loadFromFile("Sounds/EnemyMove/enemyMove4.wav");
				sound = 0;
				break;
			}
			soundPlayer.play();
			if (dir == 0 || dir == 3)
			{
				for (int i = 0; i < gameData[1].size(); i++)
					if (dynamic_cast<Ship *>(gameData[1].at(i)) != nullptr)
						dynamic_cast<Ship*>(gameData[1].at(i))->move(0);
					else
						dynamic_cast<Animation*>(gameData[1].at(i))->move(0);
				if (dir == 0)
					dir = 2;
				else
					dir = 1;
			}
			else if (dir == 1)
			{
				for (int i = 0; i < gameData[1].size(); i++)
				{
					if (dynamic_cast<Ship *>(gameData[1].at(i)) != nullptr)
					{
						if (dynamic_cast<Ship*>(gameData[1].at(i))->move(1))
							dir = 0;
					}
					else
					{
						if (dynamic_cast<Animation*>(gameData[1].at(i))->move(1))
							dir = 0;
					}
				}
			}
			else
			{
				for (int i = 0; i < gameData[1].size(); i++)
				{
					if (dynamic_cast<Ship*>(gameData[1].at(i)) != nullptr)
					{
						if (dynamic_cast<Ship*>(gameData[1].at(i))->move(2))
							dir = 3;
					}
					else
					{
						if (dynamic_cast<Animation*>(gameData[1].at(i))->move(2))
							dir = 3;
					}
				}
			}
		}

		//update enemy texture
		for (int i = 0; i < gameData[1].size(); i++)
		{
			if (ticks % (difficulty * 2) == 0)
			{
				std::string type = typeid(*gameData[1].at(i)).name();

				if (type == "class Small")
					gameData[1].at(i)->setTexture("smallShip0.png");
				else if (type == "class Medium")
					gameData[1].at(i)->setTexture("mediumShip0.png");
				else if (type == "class Large")
					gameData[1].at(i)->setTexture("largeShip0.png");
			}
			else if (ticks % difficulty == 0)
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

		//check player death
		for (int i = 0; i < gameData[0].size(); i++)
			if (dynamic_cast<Player *>(gameData[0].at(i))->getLife() == 0)
				gameData[0].erase(gameData[0].begin() + i);

		//random enemy shooting
		for (int i = 0; i < 11; i++)
		{
			if (rand() % 300 == 0)
			{
				int j = 44 + i;
				Ship * shipTemp = dynamic_cast<Ship*>(gameData[1].at(j));
				if (shipTemp != nullptr)
				{
					while (j >= 0 && !shipTemp->shoot())
					{
						j -= 11;
					}
				}
			}
		}


		//ufo spawning
		if (rand() % 875 == 0)
		{
			try
			{
				if (dynamic_cast<UFO *>(gameData[1].back())->getLife() == 0)
				{
					delete gameData[1].back();
					gameData[1].back() = new UFO(window);
				}
			}
			catch (std::exception e)
			{
				std::cout << gameData[1].size() << std::endl;
				system("pause");
			}
		}

		//check if no more enemies, then displays next level
			if(liveEnemies == 0)
			{
				level++;
				endticks = ticks;
				if(difficulty - 1 > 5)
					difficulty -= 3;
				gameData[3].push_back(new Word(window, "LEVEL " + std::to_string(level)));
				sf::Vector2f oldsize(window->getView().getSize());
				gameData[3].back()->setPosition(sf::Vector2f(oldsize.x, (3 * oldsize.y) / 4));
				gameData[3].back()->setFillColor(sf::Color::White);
				gameData[3].back()->update();
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
			}
		}

		if (ticks == endticks + 100)
		{
			gameData[3].pop_back();

			for (int j = 0; j < 11; j++)
				gameData[1].push_back(new Small(j, window));
			for (int j = 0; j < 22; j++)
			{
				gameData[1].push_back(new Medium(j, window));
			}
			for (int j = 0; j < 22; j++)
			{
				gameData[1].push_back(new Large(j, window));
			}
			
			Ship * ufo = new UFO(window);
			ufo->takeLife();
			ufo->update();
			gameData[1].push_back(ufo);

			for (int i = 0; i < 4; i++)
				gameData[2].push_back(new Shield(i, window));

			dir = 1;
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
	//E key cheat code
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		Ship * shipTemp = nullptr;
		for (int i = 0; i < gameData[1].size() && shipTemp == nullptr; i++)
			shipTemp = dynamic_cast<Ship *>(gameData[1].at(i));

		while (shipTemp != nullptr && shipTemp->getLife() != 0)
			shipTemp->takeLife();
	}

	//for each player in game data
	for (int i = 0; i < gameData[0].size(); i++)
	{
		//convert from GameObject to Player
		Player * playerTemp = dynamic_cast<Player *> (gameData[0].at(i));

		//if current index is for player 1 process player 1 controls
		if (playerTemp->player == "Player 1")
		{
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
			//dpad left move left
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				playerTemp->move(2);
			//dpad right move right
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				playerTemp->move(1);
		}
	}
}


void Game::playerShoot(sf::Event event)
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
			if (event.key.code == sf::Keyboard::W)
				playerTemp->shoot();
		}
		//if current index is for player 2 process player 2 controls
		else if (playerTemp->player == "Player 2")
		{
			//dpad up Shoots
			if (event.key.code == sf::Keyboard::Up)
				playerTemp->shoot();
		}
	}
}