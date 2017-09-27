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
	if (texture.loadFromFile("../Textures/" + fileName))
	{
		rectangle.setTexture(&texture);
		rectangle.setSize(sf::Vector2f(texture.getSize()));
		rectangle.setOrigin(rectangle.getSize().x /2, rectangle.getSize().y / 2);
	}
}

<<<<<<< HEAD
std::string GameObject::getTexture()
=======
<<<<<<< HEAD
void GameObject::setPosition(sf::Vector2f pos)
{
	rectangle.setPosition(pos);
}

void GameObject::setFillColor(sf::Color clr)
{
	rectangle.setFillColor(clr);
=======
std::string GameObject::getTexture() const
>>>>>>> c57e0e170da1a5c19d6207f7ccb009f73e444b61
{
	return textureName;
>>>>>>> 574fc9f39151f339e2034c683fb78f622ee5a535
}
