#include "stdafx.h"
#include "Medium.h"
#include "Bullet.h"


const  int FINDLATER = 5;


Medium::Medium(int x, sf::RenderWindow * wndw) : Ship(wndw)
{
	setTexture("mediumShip.png");
	points = 20;
	rectangle.setPosition(16 * (x % 11) + 28, x >= 11 ? 72 : 56);
}


Medium::~Medium()
{
	if (activeShot != nullptr)
		delete activeShot;
}
/*

void Medium::shoot()
{
	if (activeShot != nullptr)
	{
		activeShot = new Bullet(sf::Vector2i(rectangle.getPosition()), window);
		activeShot->setTexture("mediumBullet.png");
	}
}*/

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