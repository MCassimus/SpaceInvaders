#include "stdafx.h"
#include <typeinfo>
#include "Player.h"
#include "Animation.h"
#include "Shield.h"
#include "Bullet.h"


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

	//initialize bullet sounds
	bulletBuffer.loadFromFile("Sounds/bullet.wav");
	bulletSound.setBuffer(bulletBuffer);
	bulletSound.setVolume(10);

	//intialize enemy death sounds
	enemyDeathBuffer.loadFromFile("Sounds/enemyDeath.wav");
	enemyDeath.setBuffer(enemyDeathBuffer);
	enemyDeath.setVolume(10);

	extraLives = new Ship(wndw);
	extraLives->setTexture("player.png");
	extraLives->setFillColor(rectangle.getFillColor());
}


Player::~Player()
{
	if (activeShot != nullptr)
		delete activeShot;
	delete extraLives;
}


void Player::update(std::vector<GameObject *> & other)
{
	bool bulletDeath = false;

	//check bullet collision
	if (activeShot != nullptr)
	{
		if (activeShot->offScreen())
		{
			std::vector<std::string> frameFiles;
			frameFiles.push_back("bulletExplosion/bulletExplosion0.png");
			frameFiles.push_back("bulletExplosion/bulletExplosion1.png");
			frameFiles.push_back("bulletExplosion/bulletExplosion2.png");
			frameFiles.push_back("bulletExplosion/bulletExplosion3.png");

			animation.push_back(new Animation(activeShot->getPosition(), frameFiles, window));

			bulletDeath = true;
		}

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

						//sound for enemy death
						std::vector<std::string> frameFiles;
						frameFiles.push_back("enemyDeath/enemyDeath0.png");
						frameFiles.push_back("enemyDeath/enemyDeath1.png");
						frameFiles.push_back("transparent.png");
						other.at(i) = new Animation(shipTemp->getPosition(), frameFiles, window);

						enemyDeath.play();

						bulletDeath = true;
					}
					else if (type == "class Shield")
					{
						Shield * shieldTemp = dynamic_cast<Shield *>(other.at(i));
						shieldTemp->takeHealth();
						bulletDeath = true;
					}
					else if (type == "class UFO")
					{
						Ship * shipTemp = dynamic_cast<Ship *>(other.at(i));
						if (shotCount != 23 || shotCount - 23 % 15 == 0)
							score += 300;
						else
							score += shipTemp->getPoints();

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


void Player::update() 
{
};


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
	if (activeShot == nullptr && lives>0 && bulletSound.getStatus() == bulletSound.Stopped)
	{
		bulletSound.play();
		activeShot = new Bullet(sf::Vector2i(rectangle.getPosition()), window);
		activeShot->setVelocity(sf::Vector2f(0, -2));
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