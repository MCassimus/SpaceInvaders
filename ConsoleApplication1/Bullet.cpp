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


bool Bullet::collide()
{
	/*if (rectangle.getGlobalBounds().intersects(rectangle.getGlobalBounds()))
		return true;
	return false;*/
	if (rectangle.getPosition().y < 0)
		return true;
	return false;
}


bool Bullet::collide(Shield * other)
{
	if (rectangle.getGlobalBounds().intersects(other->getRectangle()->getGlobalBounds()))
	{
		textureTemp = other->getRectangle()->getTexture()->copyToImage();
		if (textureTemp.getPixel(rectangle.getPosition().x, 0) != sf::Color::Transparent)
		{
			textureTemp.setPixel(rectangle.getPosition().x, rectangle.getPosition().y, sf::Color::Transparent);
			other->setTexture(textureTemp);
			return true;
		}
		else
			return false;
	}
	else if(rectangle.getPosition().y < 0)
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