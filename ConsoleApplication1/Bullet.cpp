#include "stdafx.h"
#include "Bullet.h"
#include <SFML\Graphics.hpp>


Bullet::Bullet(sf::Vector2i pos, sf::RenderWindow * renderWindow)
{
	window = renderWindow;
	rectangle = new sf::RectangleShape(sf::Vector2f(1, 3));
	rectangle->setPosition(pos.x, pos.y);
}


Bullet::~Bullet()
{

}


bool Bullet::collide()
{
	return false;
}


void Bullet::update()
{
	rectangle->setPosition(rectangle->getPosition() + velocity);
}


void Bullet::render()
{
	window->draw(*(this->rectangle));
}