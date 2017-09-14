#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"


const  int FINDLATER = 5;


Player::Player(int x, sf::RenderWindow * wndw, char * name) : Ship(wndw)
{
	setTexture("player.png");
	points = 40;
	rectangle.setPosition(window->getView().getCenter());
	player = name;
}


Player::~Player()
{
	if (activeShot != nullptr)
		delete activeShot;
}


void Player::update()
{
	//check bullet collision
}


void Player::move(bool dir)
{
	return;
}


void Player::shoot()
{
	if (activeShot != nullptr)
		activeShot = new Bullet(sf::Vector2i(rectangle.getPosition()), window);
}

//#include "stdafx.h"
//#include "Player.h"
//#include "Bullet.h"
//
//
//const int FINDLATER = 5;
//
//Player::Player(sf::RenderWindow * wndw)
//{
//	lives = FINDLATER;
//	rectangle = sf::Rect<int>(FINDLATER, FINDLATER, FINDLATER, FINDLATER);
//	window = wndw;
//}
//
//
//Player::~Player()
//{
//}
//
//bool Player::move(bool dir)
//{
//	if (activeShot != nullptr)
//		if (activeShot->collide())
//			activeShot = nullptr;
//	if (dir)
//	{
//		if (rectangle.left < FINDLATER)
//			rectangle.left += FINDLATER;
//	}
//	else
//		if (rectangle.left > FINDLATER)
//			rectangle.left -= FINDLATER;
//
//	return false;
//}
//
//
//void Player::shoot()
//{
//	if (activeShot == nullptr)
//	{
//		activeShot = new Bullet(sf::Vector2i(rectangle.left + FINDLATER, FINDLATER),window);
//	}
//}