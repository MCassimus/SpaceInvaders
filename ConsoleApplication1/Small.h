#pragma once
#include "Ship.h"
class Small :
	public Ship
{
public:
	Small(int,sf::RenderWindow*);
	~Small();
	void update();
	bool move(int);
	void shoot();
};