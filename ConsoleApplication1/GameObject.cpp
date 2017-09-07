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
	sf::Texture textureTemp;
	textureTemp.loadFromFile("../Textures/" + fileName);
	rectangle.setTexture(&textureTemp, true);
}