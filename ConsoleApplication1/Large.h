#pragma once
#include "Ship.h"

class Large :
	public Ship
{
public:
	Large(int,sf::RenderWindow*);
	virtual ~Large();
};