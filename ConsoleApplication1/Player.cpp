#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"
#include <iostream>
#include <typeinfo>

const  int FINDLATER = 5;


Player::Player(int x, sf::RenderWindow * wndw, char * name) : Ship(wndw)
{
	setTexture("player.png");
	points = 40;
	rectangle.setPosition(sf::Vector2f(x, wndw->getView().getSize().y - 20));
	player = name;
}


Player::~Player()
{
	if (activeShot != nullptr)
		delete activeShot;
}


void Player::update(std::vector<GameObject *> other)
{
	//check bullet collision
	if (activeShot != nullptr)
	{
		for (int i = 0; i < other.size(); i++)
			if (activeShot->collide(other.at(i)))
				std::cout << typeid(*other.at(i)).name();

		activeShot->update();

		if (activeShot->offScreen())
		{
			delete activeShot;
			activeShot = nullptr;
		}
	}
}


bool Player::move(int dir)
{
	if (dir == 1)//if 1, move right
	{
		if ((rectangle.getPosition().x + rectangle.getSize().x / 2) < window->getView().getSize().x)
			rectangle.move(2, 0);
	}
	else//if 2, move left
	{
		if ((rectangle.getPosition().x - rectangle.getSize().x / 2) > 0)
			rectangle.move(-2, 0);
	}
	return true;
}


void Player::shoot()
{
	if (activeShot == nullptr)
	{
		activeShot = new Bullet(sf::Vector2i(rectangle.getPosition()), window);
		activeShot->setVelocity(sf::Vector2f(0, -2));
	}
}