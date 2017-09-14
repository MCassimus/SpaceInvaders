#include "stdafx.h"
#include "Medium.h"
#include "Bullet.h"


const  int FINDLATER = 5;


Medium::Medium(int x, sf::RenderWindow * wndw) : Ship(wndw)
{
	setTexture("mediumShip.png");
	points = 40;
}


Medium::~Medium()
{
	if (activeShot != nullptr)
		delete activeShot;
}


void Medium::update()
{
	//check bullet collision
}


void Medium::move(bool dir)
{
	return;
}


void Medium::shoot()
{
	if (activeShot != nullptr)
	{
		activeShot = new Bullet(sf::Vector2i(rectangle.getPosition()), window);
		activeShot->setTexture("mediumBullet.png");
	}
}

//bool Medium::move(bool dir)
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
//void Medium::shoot()
//{
//	sf::Vector2i pos(rectangle.left + FINDLATER, rectangle.top + FINDLATER);
//	activeShot = new Bullet(pos, window);
//}
//
//void Medium::render()
//{
//	sf::Texture texture;
//	texture.loadFromFile("MediumTexture.PNG", sf::Rect<int>(0, 0, FINDLATER, FINDLATER));
//	sf::Sprite sprite;
//	sprite.setTexture(texture);
//	sprite.setPosition(sf::Vector2f(rectangle.left, rectangle.top));
//	window->draw(sprite);
//
//	if (activeShot != nullptr)
//	{
//		texture.loadFromFile("MediumBullet.PNG", sf::Rect<int>(0, 0, FINDLATER, FINDLATER));
//		activeShot->render();
//	}
//
//}