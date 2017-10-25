#include "stdafx.h"
#include "Ship.h"
#include "Shield.h"
#include <Windows.h>
#include <iostream>


Ship::Ship(sf::RenderWindow * renderWindow) : GameObject(renderWindow)
{
	window = renderWindow;
}


Ship::~Ship()
{
	if (activeShot != nullptr)
	{
		delete activeShot;
		activeShot = nullptr;
	}
}


void Ship::render()
{
	if(lives>0)
		window->draw(rectangle);
	if (activeShot != nullptr)
		activeShot->render();
	if (lives > 1)
		this->renderLives();
	if (!animation.empty())
		for(int i = 0; i < animation.size(); i++)
			animation.at(i)->render();
}


int Ship::getLife() const
{
	if (this != nullptr)
		return lives;
	else
		return 0;
}


void Ship::takeLife()
{
	lives--;//Below is a terrible way to deal with strings
	if (lives == 0 && typeid(*this).name() == "class UFO")
		this->update();
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

						if (shipTemp->animation.empty())
						{

							shipTemp->takeLife();

							//animation for enemy death
							std::vector<std::string> frameFiles;
							frameFiles.push_back("player.png");
							frameFiles.push_back("transparent.png");
							frameFiles.push_back("player.png");
							frameFiles.push_back("transparent.png");
							frameFiles.push_back("player.png");
							frameFiles.push_back("transparent.png");
							frameFiles.push_back("player.png");
							frameFiles.push_back("transparent.png");
							frameFiles.push_back("player.png");
							frameFiles.push_back("transparent.png");
							sf::Vector2f pos = shipTemp->getPosition();
							pos.y - 8;
							Animation * animationTemp = new Animation(pos, frameFiles, window);
							animationTemp->setColor(sf::Color::Red);
							shipTemp->animation.push_back(animationTemp);
						}
												
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

	sf::Vector2f position = rectangle.getPosition();
	if (lives <= 0)
	{
		position.y = window->getView().getSize().y;
		rectangle.setPosition(position);
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
			if (position.x >= window->getView().getSize().x - 6)
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
	//else
	//{
	//	position.y = window->getView().getSize().y;
	//	rectangle.setPosition(position);
	//}
	return false;
}


bool Ship::shoot()
{
	if (activeShot == nullptr && lives>0)
	{
		sf::Vector2i pos = sf::Vector2i(rectangle.getPosition());
		pos.y += 8;
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