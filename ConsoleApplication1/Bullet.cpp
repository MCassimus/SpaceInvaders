#include "stdafx.h"
#include "Bullet.h"
#include <SFML\Graphics.hpp>


Bullet::Bullet(sf::Vector2i pos, sf::RenderWindow * renderWindow)
{
	window = renderWindow;
	rectangle = new sf::RectangleShape(sf::Vector2f(1, 3));
	rectangle->setPosition(pos.x, pos.y);
	rectangle->setFillColor(sf::Color::Green);
}


Bullet::~Bullet()
{
	delete rectangle;
}


bool Bullet::collide()
{
	if (rectangle->getGlobalBounds().intersects(rectangle->getGlobalBounds()))
		return true;
	return false;
}


void Bullet::update()
{
	rectangle->setPosition(rectangle->getPosition() + velocity);
}


void Bullet::render()
{
	window->draw(*rectangle);
}