#pragma once
#include "Ship.h"
class Medium :
	public Ship
{
public:
	Medium(int, sf::RenderWindow*);
	~Medium();
	void update();
	bool move(int);
	void shoot();
};