#include "stdafx.h"
#include "Small.h"
#include "Bullet.h"
#include <iostream>


const  int FINDLATER = 5;


Small::Small(int x, sf::RenderWindow * wndw) : Ship(wndw)
{
	setTexture("smallShip.png");
	points = 40;
	rectangle.setPosition(16 * x + 28, 40);
	rectangle.setSize(sf::Vector2f(8, 8));
	//rectangle.setPosition(16 * x + 40, 100);
	//rectangle.setPosition(x, 50);
}


Small::~Small()
{
	if (activeShot != nullptr)
		delete activeShot;
}


void Small::update()
{
	//check bullet collision
}


void Small::shoot()
{
	if (activeShot != nullptr)
	{
		activeShot = new Bullet(sf::Vector2i(rectangle.getPosition()), window);
		activeShot->setTexture("smallBullet.png");
	}
}
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