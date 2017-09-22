#include "stdafx.h"
#include "Ship.h"


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


void Ship::shoot()
{
	if (activeShot == nullptr)
	{
		activeShot = new Bullet(sf::Vector2i(rectangle.getPosition()), window);
	}
}