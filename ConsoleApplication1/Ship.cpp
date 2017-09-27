#include "stdafx.h"
#include "Ship.h"
#include "Shield.h"
#include <iostream>


Ship::Ship(sf::RenderWindow * renderWindow) : GameObject(renderWindow)
{
	window = renderWindow;
}


Ship::~Ship()
{
}


void Ship::render()
{
	if(lives>0)
		window->draw(rectangle);
	if (activeShot != nullptr)
		activeShot->render();
	if (lives > 1)
		this->renderLives();
}

int Ship::getLife() const
{
	return lives;
}

void Ship::takeLife()
{
	lives--;
}

int Ship::getPoints() const
{
	return points;
}

void Ship::renderLives()
{
}


void Ship::update(std::vector<GameObject *> other)
{
	bool bulletDeath = false;

	//check bullet collision
	if (activeShot != nullptr)
	{
		if (activeShot->offScreen())
			bulletDeath = true;

		if (!bulletDeath)
		{
			for (int i = 0; i < other.size(); i++)
			{
				std::string type = typeid(*other.at(i)).name();

				if (activeShot->collide(other.at(i)))
				{
					if (type == "class Player")
					{
						Ship * shipTemp = dynamic_cast<Ship *>(other.at(i));
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

bool Ship::move(int dir)
{
	if (activeShot != nullptr)
		if (activeShot->collide(this))
			activeShot = nullptr;
	sf::Vector2f position = rectangle.getPosition();
	if (lives > 0)
	{
		if (dir == 0)
		{
			position.y += 8;
			rectangle.setPosition(position);
		}
		else if (dir == 1)
		{
			position.x += 2;
			rectangle.setPosition(position);
			if (position.x >= 212)
				return true;
		}
		else
		{
			position.x -= 2;
			rectangle.setPosition(position);
			if (position.x <= 6)
				return true;
		}
	}
	else
	{
		position.y = window->getView().getSize().y;
		rectangle.setPosition(position);
	}
	return false;
}


bool Ship::shoot()
{
	if (activeShot == nullptr&&lives>0)
	{
		sf::Vector2i pos = sf::Vector2i(rectangle.getPosition());
		pos.y += 4;
		activeShot = new Bullet(pos, window);
		switch (rand() % 3)
		{
		case 0:
			activeShot->setTexture("bullet1.png");
			break;
		default:
			activeShot->setTexture("bullet2.png");
			break;
		}
	}
	return lives > 0;
}


void Ship::update()
{
	if (activeShot != nullptr)
	{
		if (activeShot->offScreen())
		{
			delete activeShot;
			activeShot = nullptr;
		}
		else
			activeShot->update();
	}
}