#include "stdafx.h"
#include "Small.h"
#include "Bullet.h"


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
	static bool dir;
	if (move(dir))
		dir = !dir;
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

bool Small::move(int dir)
{
	if (activeShot != nullptr)
		if (activeShot->collide(this))
			activeShot = nullptr;
	sf::Vector2f position = rectangle.getPosition();
	if (dir == 0)
	{
		position.y += 8;
		rectangle.setPosition(position);
	}
	else if (dir == 1)
	{
		position.x += 2;
		rectangle.setPosition(position);
		if(position.x>=206)
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