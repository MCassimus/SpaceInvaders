#pragma once
#include "Ship.h"
class Large :
	public Ship
{
public:
	Large(int,sf::RenderWindow*);
	~Large();
	void render();
	void update();
	void move(bool);
	void shoot();
};