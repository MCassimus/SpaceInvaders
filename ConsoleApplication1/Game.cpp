#include "stdafx.h"
#include "Game.h"
#include "Shield.h"
#include <iostream>


Game::Game(sf::RenderWindow * renderWindow)
{
	window = renderWindow;
	shield = new Shield(window);
	//display score information
	arcadeFont.loadFromFile("../ArcadeFont.otf");
	scorePrompt = sf::RectangleShape(sf::Vector2f(400, 16));
	scorePromptTexture.loadFromFile("../Textures/scorePrompt.png");
	scorePrompt.setTexture(&scorePromptTexture);
	scorePrompt.setPosition(scorePrompt.getPosition().x, 5);


	texture.loadFromFile("../Textures/player.png");
	rectangle = sf::RectangleShape(sf::Vector2f(20, 12));
	rectangle.setTexture(&texture);
	rectangle.setOrigin(rectangle.getSize().x / 2, 0);
	rectangle.setPosition(window->getSize().x / 2, window->getSize().y - 75);
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

	shield->update();
	
	
	if (bullet != nullptr)
	{
		bullet->update();
		if (bullet->collide())
		{
			delete bullet;
			bullet = nullptr;
		}
	}

	/*
	for(int x = 0; x < ENEMYARRSIZEX; x++)
		for(int y = 0; y < ENEMYARRSIZEY; y++)
			enemies[x][y]->
	*/

	if(window->isOpen()/* && player1 != nullptr || player2 != nullptr*/ )
		return true;//return true while players are alive & game open
	return false;
}


void Game::render()
{
	window->clear();

	//draw point display
	window->draw(scorePrompt);
	window->draw(rectangle);
	//draw shields
	shield->render();
	if(bullet != nullptr)
		bullet->render();

	window->display();
}


void Game::processKeyboard()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		rectangle.move(-1, 0);
	}
		//std::cout << "Player 1  - MOVE LEFT\n";
	//player1.move(false);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		rectangle.move(1, 0);
	}
		//std::cout << "Player 1 - MOVE RIGHT\n";
	//player1.move(true);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if(bullet == nullptr)
			bullet = new Bullet(sf::Vector2i(rectangle.getPosition()), window);
	}
		//std::cout << "Player 1 - FIRE\n";
	//player1.shoot();

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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			window->setSize(sf::Vector2u(600, 600));
}