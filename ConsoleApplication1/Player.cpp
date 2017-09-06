#include "stdafx.h"
#include "Player.h"


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

bool Player::move(bool )
{
	if
	return false;
}

bool Player::shoot()
{
	return false;
}
