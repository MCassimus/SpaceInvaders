#include "stdafx.h"
#include "Large.h"
#include "Bullet.h"


const  int FINDLATER = 5;


Large::Large(int x, sf::RenderWindow * wndw) : Ship(wndw)
{
	setTexture("largeShip.png");
	points = 40;
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


void Large::move(bool dir)
{
	return;
}


void Large::shoot()
{
	if (activeShot != nullptr)
	{
		activeShot = new Bullet(sf::Vector2i(rectangle.getPosition()), window);
		activeShot->setTexture("largeBullet.png");
	}
}

//bool Large::move(bool dir)
//{
//	if (activeShot != nullptr)
//		if (activeShot->collide())
//			activeShot = nullptr;
//	static bool lastdir = true;
//	if (dir != lastdir)
//	{
//		rectangle.top += FINDLATER;
//		lastdir = dir;
//	}
//	else if (dir)
//	{
//		rectangle.left += FINDLATER;
//		if (rectangle.left >= FINDLATER)
//			return true;
//	}
//	else
//	{
//		rectangle.left -= FINDLATER;
//
//		if (rectangle.left <= FINDLATER)
//			return true;
//	}
//	return false;
//}
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