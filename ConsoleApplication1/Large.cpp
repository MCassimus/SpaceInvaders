#include "stdafx.h"
#include "Large.h"
#include "Bullet.h"


const  int FINDLATER = 5;


Large::Large(int x, sf::RenderWindow * wndw) : Ship(wndw)
{
	setTexture("largeShip.png");
	points = 40;
	rectangle.setPosition(x, 50);
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

bool Large::move(bool dir)
{
	if (activeShot != nullptr)
		if (activeShot->collide(this))
			activeShot = nullptr;
	static bool lastdir = true;
	sf::Vector2f position = rectangle.getPosition();
	if (dir != lastdir)
	{
		position.y += 8;
		lastdir = dir;
	}
	else if (dir)
	{
		position.x += 2;
		rectangle.setPosition(position);
		if (position.x >= 206)
			return true;
	}
	else
	{
		position.x -= 2;
		rectangle.setPosition(position);
		if (position.x <= 0)
			return true;
	}
	return false;
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