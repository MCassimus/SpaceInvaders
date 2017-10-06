#include "stdafx.h"
#include "Large.h"


Large::Large(int x, sf::RenderWindow * wndw) : Ship(wndw)
{
	setTexture("largeShip0.png");
	points = 10;
	rectangle.setPosition(16*(x%11)+28, (x>=11)?104:88);
}


Large::~Large()
{
	if (activeShot != nullptr)
		delete activeShot;
}