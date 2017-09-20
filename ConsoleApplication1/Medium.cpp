#include "stdafx.h"
#include "Medium.h"
#include "Bullet.h"


const  int FINDLATER = 5;


Medium::Medium(int x, sf::RenderWindow * wndw) : Ship(wndw)
{
	setTexture("mediumShip.png");
	points = 40;
	rectangle.setPosition(x, 50);
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


void Medium::shoot()
{
	if (activeShot != nullptr)
	{
		activeShot = new Bullet(sf::Vector2i(rectangle.getPosition()), window);
		activeShot->setTexture("mediumBullet.png");
	}
}

bool Medium::move(bool dir)
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