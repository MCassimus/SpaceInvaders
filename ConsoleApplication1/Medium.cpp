#include "stdafx.h"
#include "Medium.h"


Medium::Medium(int x, sf::RenderWindow * wndw) : Ship(wndw)
{
	setTexture("mediumShip0.png");
	points = 20;
	rectangle.setPosition(16 * (x % 11) + 28, x >= 11 ? 72 : 56);
}


Medium::~Medium()
{
	if (activeShot != nullptr)
		delete activeShot;
}