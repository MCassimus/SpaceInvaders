#pragma once
#include "Ship.h"
class Small :
	public Ship
{
public:
	Small(int,sf::RenderWindow*);
	~Small();
	virtual bool move(bool);
	virtual void shoot();
	virtual void render();
};

