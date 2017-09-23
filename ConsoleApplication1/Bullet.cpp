#include "stdafx.h"
#include "Bullet.h"
#include <SFML\Graphics.hpp>

Bullet::Bullet(sf::Vector2i pos, sf::RenderWindow * renderWindow) : GameObject(renderWindow)
{
	rectangle = sf::RectangleShape(sf::Vector2f(1, 7));
	rectangle.setPosition(pos.x, pos.y);
	rectangle.setFillColor(sf::Color::Green);
}


Bullet::~Bullet()
{
}


void Bullet::update()
{
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