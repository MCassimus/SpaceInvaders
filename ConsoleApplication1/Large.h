#pragma once
#include "Ship.h"
class Large :
	public Ship
{
public:
	Large(int,sf::RenderWindow*);
	~Large();
	void update();
	bool move(int);
	void shoot();
};