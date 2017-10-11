#pragma once
#include "Ship.h"

class Medium :
	public Ship
{
public:
	Medium(int, sf::RenderWindow*);
	virtual ~Medium();
};