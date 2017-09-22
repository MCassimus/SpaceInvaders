#include "stdafx.h"
#include "Shield.h"


Shield::Shield(sf::RenderWindow * renderWindow) : GameObject(renderWindow)
{
	setTexture("/Shields/shield15.png");
	rectangle.setPosition(rectangle.getPosition().x, window->getSize().y - 100);
}


Shield::~Shield()
{
}


void Shield::update()
{
	//update texture to match
	if (health <= 1)
		setTexture("/Shield/Shield" + std::to_string(health) + ".png");
}


void Shield::takeHealth()
{
	health--;
}