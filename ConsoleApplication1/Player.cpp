#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"
#include <typeinfo>
#include <iostream>

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
	bool bulletDeath = false;

	//check bullet collision
	if (activeShot != nullptr)
	{
		if (activeShot->offScreen())
			bulletDeath = true;

		if(!bulletDeath)
		{
			for (int i = 0; i < other.size(); i++)
			{
				if (activeShot->collide(other.at(i)))
				{
					std::string type = typeid(*other.at(i)).name();

					if (type == "class Large" || type == "class Medium" || type == "class Small")
					{
						Ship * shipTemp = dynamic_cast<Ship *>(other.at(i));
						shipTemp->takeLife();
						bulletDeath = true;
					}
				}
			}
		}

		if (bulletDeath)
		{
			delete activeShot;
			activeShot = nullptr;
		}
		else
			activeShot->update();
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