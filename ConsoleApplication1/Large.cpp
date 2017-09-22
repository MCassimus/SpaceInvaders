#include "stdafx.h"
#include "Large.h"
#include "Bullet.h"


const  int FINDLATER = 5;


Large::Large(int x, sf::RenderWindow * wndw) : Ship(wndw)
{
	setTexture("largeShip.png");
	points = 10;
	rectangle.setPosition(16*(x%11)+28, (x>=11)?88:104);
}


Large::~Large()
{
	if (activeShot != nullptr)
		delete activeShot;
}


void Large::update()
{
	//check bullet collision
}


void Large::shoot()
{
	if (activeShot != nullptr)
	{
		activeShot = new Bullet(sf::Vector2i(rectangle.getPosition()), window);
		activeShot->setTexture("largeBullet.png");
	}
}
//
//void Large::shoot()
//{
//	sf::Vector2i pos(rectangle.left + FINDLATER, rectangle.top + FINDLATER);
//	activeShot = new Bullet(pos, window);
//}
//
//void Large::render()
//{
//	window->draw(rectangle);
//
//	if (activeShot != nullptr)
//	{
//		activeShot->setTexture("largeBullet.png");
//		activeShot->render();
//	}
//}