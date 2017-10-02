#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"
#include <typeinfo>
#include <iostream>
#include "Shield.h"
#include "Animation.h"

const  int FINDLATER = 5;


Player::Player(int x, sf::RenderWindow * wndw, char * name) : Ship(wndw)
{
	player = name;
	if (player == "Player 1")
		rectangle.setFillColor(sf::Color::Green);
	else if (name == "Player 2")
		rectangle.setFillColor(sf::Color::White);
	setTexture("player.png");
	points = 40;
	rectangle.setPosition(sf::Vector2f(x, wndw->getView().getSize().y - 40));
	rectangle.setOrigin(rectangle.getOrigin().x, 0);//set origin to top of player for bullet to spawn correctly
	lives = 3;

	extraLives = new Ship(wndw);
	extraLives->setTexture("player.png");
	extraLives->setFillColor(rectangle.getFillColor());
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
			std::vector<std::string> frameFiles;
			frameFiles.push_back("bulletExplosion/bulletExplosion0.png");
			frameFiles.push_back("bulletExplosion/bulletExplosion1.png");
			frameFiles.push_back("bulletExplosion/bulletExplosion2.png");
			frameFiles.push_back("bulletExplosion/bulletExplosion3.png");

			if (activeShot->offScreen())
				activeShot->setPosition(sf::Vector2f(activeShot->getPosition().x, 8));

			animation.push_back(new Animation(activeShot->getPosition(), frameFiles, window));

			delete activeShot;
			activeShot = nullptr;
		}
		else
			activeShot->update();
	}
	if (!animation.empty())
	{
		for (int i = 0; i < animation.size(); i++)
		{
			if (animation.at(i)->isDone())
				animation.erase(animation.begin() + i);
			else
				animation.at(i)->update();
		}
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
	if (activeShot == nullptr&&lives>0)
	{
		activeShot = new Bullet(sf::Vector2i(rectangle.getPosition()), window);
		activeShot->setVelocity(sf::Vector2f(0, -1.5));
		shotCount++;
	}
}

int Player::getScore() const
{
	return score;
}

void Player::renderLives()
{
	for (int i = 1; i < lives; i++)
	{
		extraLives->setPosition(sf::Vector2f(player == "Player 1" ? i * 16 - 8 : 224 - i * 16, window->getView().getSize().y - 8));
		extraLives->render();
	}
}
