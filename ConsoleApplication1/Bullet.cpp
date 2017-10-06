#include "stdafx.h"
#include "Bullet.h"
#include <SFML\Graphics.hpp>
#include "Animation.h"

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
	if (rectangle.getPosition().y >= window->getView().getSize().y - 65)
		rectangle.setFillColor(sf::Color::Green);

	if (flipTick % 10 == 0)
	{
		flipTick = 1;
		rectangle.scale(textureScale, 1);
		textureScale *= -1;
	}
	else
		flipTick++;

	rectangle.move(velocity);
}

void Bullet::setVelocity(sf::Vector2f newVelocity)
{
	velocity = newVelocity;
}


bool Bullet::offScreen()
{
	if (rectangle.getPosition().y < 20 || (rectangle.getPosition().y >= window->getView().getSize().y - 18))
	{
		rectangle.setPosition(rectangle.getPosition().x, 20);
		return true;
	}
	return false;
}