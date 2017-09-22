#include "stdafx.h"
#include "Ship.h"
#include <iostream>


Ship::Ship(sf::RenderWindow * renderWindow) : GameObject(renderWindow)
{
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
				if (activeShot->collide(other.at(i)))
				{
					std::string type = typeid(*other.at(i)).name();

					if (type == "class Player")
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