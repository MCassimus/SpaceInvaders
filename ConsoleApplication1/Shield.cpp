#include "stdafx.h"
#include "Shield.h"


Shield::Shield(sf::RenderWindow * renderWindow) : GameObject(renderWindow)
{
	setTexture("shield.png");
	rectangle.setPosition(rectangle.getPosition().x, window->getSize().y - 100);
}


Shield::~Shield()
{
}