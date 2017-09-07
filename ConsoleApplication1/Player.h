#pragma once
#include "Ship.h"
class Player :
	public Ship
{
public:
	Player(int, sf::RenderWindow*);
	~Player();
	void render();
	void update();
	void move(bool);
	void shoot();
};