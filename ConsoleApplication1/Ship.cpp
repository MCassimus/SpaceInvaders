#include "stdafx.h"
#include "Ship.h"


Ship::Ship(sf::RenderWindow * renderWindow) : GameObject(renderWindow)
{
}


Ship::~Ship()
{
}


void Ship::render()
{
	window->draw(rectangle);
	if (activeShot != nullptr)
		activeShot->render();
}


void Ship::update()
{

}