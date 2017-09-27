#include "stdafx.h"
#include "Bullet.h"
#include <SFML\Graphics.hpp>

Bullet::Bullet(sf::Vector2i pos, sf::RenderWindow * renderWindow) : GameObject(renderWindow)
{
	rectangle = sf::RectangleShape(sf::Vector2f(1, 6));
	rectangle.setPosition(pos.x, pos.y);
	rectangle.setFillColor(sf::Color::White);
	
}


Bullet::~Bullet()
{
}


void Bullet::update()
{

	if (rectangle.getPosition().y >= window->getView().getSize().y - 60)
	{
		rectangle.setFillColor(sf::Color::Green);
	}

	//rectangle.scale(-1, 1);


	rectangle.move(velocity);
}

void Bullet::setVelocity(sf::Vector2f newVelocity)
{
	velocity = newVelocity;
}


bool Bullet::offScreen()
{
	if (rectangle.getPosition().y < 0 || (rectangle.getPosition().y >= window->getView().getSize().y))
		return true;
	return false;
}