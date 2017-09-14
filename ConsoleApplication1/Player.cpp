#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"


const  int FINDLATER = 5;


Player::Player(int x, sf::RenderWindow * wndw, char * name) : Ship(wndw)
{
	setTexture("player.png");
	points = 40;
	rectangle.setPosition(sf::Vector2f(x, wndw->getView().getSize().y - 20));
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
	if (dir)
		rectangle.move(2, 0);
	else
		rectangle.move(-2, 0);
	return;
}


void Player::shoot()
{
	if (activeShot != nullptr)
		activeShot = new Bullet(sf::Vector2i(rectangle.getPosition()), window);
}