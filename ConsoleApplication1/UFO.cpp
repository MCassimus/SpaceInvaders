#include "stdafx.h"
#include "UFO.h"
#include <iostream>


UFO::UFO(sf::RenderWindow * window) : Ship(window)
{
	direction = rand() % 2;

	if(direction == 0)
		rectangle.setPosition(sf::Vector2f(0, 28));
	else if(direction == 1)
		rectangle.setPosition(sf::Vector2f(window->getView().getSize().x, 28));

	points = 50 * ((rand() % 4) + 1);

	buffer.loadFromFile("Sounds/UFO.wav");
	ufoSound.setBuffer(buffer);
	ufoSound.setLoop(true);
	ufoSound.setVolume(10);
	ufoSound.play();

	setTexture("ufo.png");

	permDeath = false;
}


UFO::~UFO()
{
	ufoSound.stop();
	if (activeShot != nullptr)
	{
		delete activeShot;
		std::cout << "UFO has bullet" << std::endl;
		system("pause");
	}
}


bool UFO::move(int dir)
{
	if (direction == 0)//move right
		rectangle.move(sf::Vector2f(0.5, 0));
	else if (direction == 1)//move left
		rectangle.move(sf::Vector2f(-0.5, 0));
	
	//if offscreen kill ufo
	if (rectangle.getPosition().x < -10 || rectangle.getPosition().x > window->getView().getSize().x + 10)
	{
		while (getLife() >= 0)
			takeLife();
		ufoSound.stop();
	}

	return false;
}


bool UFO::shoot()
{
	return true;
}


void UFO::update()
{
	if (getLife() == 0)
		ufoSound.stop();
	move(direction);
}

void UFO::actuallyDie()
{
	permDeath = true;
}

bool UFO::actuallyDead()
{
	return permDeath;
}
