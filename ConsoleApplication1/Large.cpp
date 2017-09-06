#include "stdafx.h"
#include "Large.h"
#include "Bullet.h"


const  int FINDLATER = 5;


Large::Large(int x, bool top, sf::RenderWindow * wndw)
{
	rectangle = sf::Rect<int>(FINDLATER*x + FINDLATER, top?FINDLATER:FINDLATER, FINDLATER, FINDLATER);
	points = 20;
	window = wndw;
}


Large::~Large()
{
}

bool Large::move(bool dir)
{
	if (activeShot != nullptr)
		if (activeShot->collide())
			activeShot = nullptr;
	static bool lastdir = true;
	if (dir != lastdir)
	{
		rectangle.top += FINDLATER;
		lastdir = dir;
	}
	else if (dir)
	{
		rectangle.left += FINDLATER;
		if (rectangle.left >= FINDLATER)
			return true;
	}
	else
	{
		rectangle.left -= FINDLATER;

		if (rectangle.left <= FINDLATER)
			return true;
	}
	return false;
}

void Large::shoot()
{
	sf::Vector2i pos(rectangle.left + FINDLATER, rectangle.top + FINDLATER);
	activeShot = new Bullet(pos, window);
}

void Large::render()
{
	sf::Texture texture;
	texture.loadFromFile("LargeTexture.PNG", sf::Rect<int>(0, 0, FINDLATER, FINDLATER));
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setPosition(sf::Vector2f(rectangle.left, rectangle.top));
	window->draw(sprite);

	if (activeShot != nullptr)
	{
		texture.loadFromFile("LargeBullet.PNG", sf::Rect<int>(0, 0, FINDLATER, FINDLATER));
		activeShot->render();
	}

}