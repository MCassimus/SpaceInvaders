#include "stdafx.h"
#include "Shield.h"


Shield::Shield(int id, sf::RenderWindow * renderWindow) : GameObject(renderWindow)
{
	setTexture("/Shields/shield15.png");
	rectangle.setPosition((window->getView().getSize().x / 4) * id, window->getView().getSize().y - 40);
	rectangle.move(window->getView().getSize().x / 8, 0);
}


Shield::~Shield()
{
}


void Shield::update()
{
	//update texture to match
	if (health >= 1)
		setTexture("/Shields/Shield" + std::to_string(health) + ".png");
}


void Shield::takeHealth()
{
	health--;
}

int Shield::getHealth() const
{
	return health;
}
