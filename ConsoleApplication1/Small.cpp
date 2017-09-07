#include "stdafx.h"
#include "Small.h"
#include "Bullet.h"


const  int FINDLATER = 5;


Small::Small(int x, sf::RenderWindow * wndw) : Ship(wndw)
{
	setTexture("smallShip.png");
	points = 40;
}


Small::~Small()
{
	if (activeShot != nullptr)
		delete activeShot;
}


void Small::render()
{
	window->draw(rectangle);

	if (activeShot != nullptr)
		activeShot->render();
}


void Small::update()
{
	//check bullet collision
}


void Small::move(bool dir)
{
	return;
}


void Small::shoot()
{
	if (activeShot != nullptr)
	{
		activeShot = new Bullet(sf::Vector2i(rectangle.getPosition()), window);
		activeShot->setTexture("smallBullet.png");
	}
}

//bool Small::move(bool dir)
//{
//	if (activeShot != nullptr)
//		if (activeShot->collide(this))
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
//void Small::shoot()
//{
//	sf::Vector2i pos(rectangle.left + FINDLATER, rectangle.top + FINDLATER);
//	activeShot = new Bullet(pos, window);
//}
//
//void Small::render()
//{
//	sf::Texture texture;
//	texture.loadFromFile("SmallTexture.PNG", sf::Rect<int>(0, 0, FINDLATER, FINDLATER));
//	sf::Sprite sprite;
//	sprite.setTexture(texture);
//	sprite.setPosition(sf::Vector2f(rectangle.left, rectangle.top));
//	window->draw(sprite);
//
//	if (activeShot != nullptr)
//	{
//		texture.loadFromFile("smallBullet.PNG", sf::Rect<int>(0, 0, FINDLATER, FINDLATER));
//		activeShot->render();
//	}
//
//}