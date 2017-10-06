#include "stdafx.h"
#include "GameObject.h"


GameObject::GameObject(sf::RenderWindow * renderWindow)
{
	window = renderWindow;
}


GameObject::~GameObject()
{
}


void GameObject::render()
{
	window->draw(rectangle);
}


void GameObject::update()
{
}


bool GameObject::collide(GameObject * other)
{
	if (other->rectangle.getGlobalBounds().intersects(rectangle.getGlobalBounds()))
		return true;
	return false;
}


void GameObject::setTexture(std::string fileName)
{
	textureName = fileName;
	if (texture.loadFromFile("Textures/" + fileName))
	{
		rectangle.setTexture(&texture);
		rectangle.setSize(sf::Vector2f(texture.getSize()));
		rectangle.setOrigin(rectangle.getSize().x /2, rectangle.getSize().y / 2);
	}
}


void GameObject::setPosition(sf::Vector2f pos)
{
	rectangle.setPosition(pos);
}


void GameObject::setFillColor(sf::Color clr)
{
	rectangle.setFillColor(clr);
}


std::string GameObject::getTexture() const
{
	return textureName;
}

sf::Vector2f GameObject::getPosition()
{
	return rectangle.getPosition();
}
