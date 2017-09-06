#include "stdafx.h"
#include "Bullet.h"
#include <SFML\Graphics.hpp>

Bullet::Bullet(sf::Vector2i pos, sf::RenderWindow * renderWindow)
{
	window = renderWindow;
	rectangle = sf::RectangleShape(sf::Vector2f(1, 3));
	rectangle.setPosition(pos.x, pos.y);
	rectangle.setFillColor(sf::Color::Green);
}


Bullet::~Bullet()
{
}


bool Bullet::collide(Ship * other)
{
	if (rectangle.getPosition().y >= 0 || rectangle.getPosition().y <= window->getSize().y)
		if (rectangle.getGlobalBounds().intersects(other.getGlobalBounds()))
			return true;
	return false;
}


bool Bullet::collide(Shield * other)
{
	if (rectangle.getPosition().y >= 0 || rectangle.getPosition().y <= window->getSize().y)
		if(rectangle.getGlobalBounds().intersects(other->getRectangle()->getGlobalBounds()))
			return true;
	return false;
}


void Bullet::update()
{
	rectangle.setPosition(rectangle.getPosition() + velocity);
}


void Bullet::render()
{
	window->draw(rectangle);
}


void Bullet::setTexture(std::string texture)
{
	sf::Texture textureTemp;
	textureTemp.loadFromFile("../Textures/" + texture + ".png");
	rectangle.setTexture(&textureTemp);
}