#pragma once
#include "Ship.h"
class Large :
	public Ship
{
public:
	Large(int, bool,sf::RenderWindow*);
	~Large();
	virtual bool move(bool);
	virtual void shoot();
	virtual void render();
};

