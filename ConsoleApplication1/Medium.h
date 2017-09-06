#pragma once
#include "Ship.h"
class Medium :
	public Ship
{
public:
	Medium(int, bool,sf::RenderWindow*);
	~Medium();
	virtual bool move(bool);
	virtual void shoot();
	virtual void render();
};

