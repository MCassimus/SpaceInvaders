#include "stdafx.h"
#include "Small.h"
#include "Bullet.h"


Small::Small(int x, sf::RenderWindow * wndw) : Ship(wndw)
{
	setTexture("smallShip0.png");
	points = 30;
	rectangle.setPosition(16 * x + 28, 40);
	rectangle.setSize(sf::Vector2f(8, 8));
}


Small::~Small()
{
	if (activeShot != nullptr)
		delete activeShot;
}