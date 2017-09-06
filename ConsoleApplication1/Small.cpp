#include "stdafx.h"
#include "Small.h"
#include "Bullet.h"


const  int FINDLATER = 5;


Small::Small(int x, sf::RenderWindow * wndw)
{
	rectangle = sf::Rect<int>(FINDLATER*x + FINDLATER, FINDLATER, FINDLATER, FINDLATER);
	points = 40;
	window = wndw;
}


Small::~Small()
{
}

bool Small::move(bool dir)
{
	if (activeShot != nullptr)
		if (activeShot->collide(this))
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

void Small::shoot()
{
	sf::Vector2i pos(rectangle.left + FINDLATER, rectangle.top + FINDLATER);
	activeShot = new Bullet(pos, window);
}

void Small::render()
{
	sf::Texture texture;
	texture.loadFromFile("SmallTexture.PNG", sf::Rect<int>(0, 0, FINDLATER, FINDLATER));
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setPosition(sf::Vector2f(rectangle.left, rectangle.top));
	window->draw(sprite);

	if (activeShot != nullptr)
	{
		texture.loadFromFile("smallBullet.PNG", sf::Rect<int>(0, 0, FINDLATER, FINDLATER));
		activeShot->render();
	}

}