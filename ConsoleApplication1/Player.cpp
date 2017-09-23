#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"
#include <typeinfo>
#include <iostream>
#include "Shield.h"

const  int FINDLATER = 5;


Player::Player(int x, sf::RenderWindow * wndw, char * name) : Ship(wndw)
{
	setTexture("player.png");
	points = 40;
	rectangle.setPosition(sf::Vector2f(x, wndw->getView().getSize().y - 20));
	player = name;
	lives = 3;
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
						score += shipTemp->getPoints();
						shipTemp->takeLife();
						bulletDeath = true;
					}
					else if (type == "class Shield")
					{
						Shield * shieldTemp = dynamic_cast<Shield *>(other.at(i));
						shieldTemp->takeHealth();
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


void Player::update() {};


bool Player::move(int dir)
{
	if (dir == 1)//if 1, move right
	{
		if ((rectangle.getPosition().x + rectangle.getSize().x / 2) < window->getView().getSize().x)
			rectangle.move(1, 0);
	}
	else//if 2, move left
	{
		if ((rectangle.getPosition().x - rectangle.getSize().x / 2) > 0)
			rectangle.move(-1, 0);
	}
	return true;
}


void Player::shoot()
{
	if (activeShot == nullptr)
	{
		activeShot = new Bullet(sf::Vector2i(rectangle.getPosition()), window);
		activeShot->setVelocity(sf::Vector2f(0, -1.25));
	}
}

int Player::getScore() const
{
	return score;
}
