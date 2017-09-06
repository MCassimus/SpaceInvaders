#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"


const int FINDLATER = 5;

Player::Player(sf::RenderWindow * wndw)
{
	lives = FINDLATER;
	rectangle = sf::Rect<int>(FINDLATER, FINDLATER, FINDLATER, FINDLATER);
	window = wndw;
}


Player::~Player()
{
}

bool Player::move(bool dir)
{
	if (activeShot != nullptr)
		if (activeShot->collide())
			activeShot = nullptr;
	if (dir)
	{
		if (rectangle.left < FINDLATER)
			rectangle.left += FINDLATER;
	}
	else
		if (rectangle.left > FINDLATER)
			rectangle.left -= FINDLATER;

	return false;
}


void Player::shoot()
{
	if (activeShot == nullptr)
	{
		activeShot = new Bullet(sf::Vector2i(rectangle.left + FINDLATER, FINDLATER),window);
	}
}
