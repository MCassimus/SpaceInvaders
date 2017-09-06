#include "stdafx.h"
#include "Bullet.h"
#include <SFML\Graphics.hpp>

Bullet::Bullet(sf::Vector2i pos, sf::RenderWindow * renderWindow) : GameObject(renderWindow)
{
	rectangle = sf::RectangleShape(sf::Vector2f(1, 3));
	rectangle.setPosition(pos.x, pos.y);
	rectangle.setFillColor(sf::Color::Green);
}


Bullet::~Bullet()
{
}