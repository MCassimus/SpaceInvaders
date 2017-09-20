#pragma once
#include "Ship.h"
class Player :
	public Ship
{
public:
	Player(int, sf::RenderWindow*, char * = "Player 1");
	~Player();
	void update();
	bool move(bool);
	void shoot();
	char * player = nullptr;
};