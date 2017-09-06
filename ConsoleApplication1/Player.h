#pragma once
#include "Ship.h"

class Player :
	public Ship
{
public:
	Player();
	~Player();

	virtual bool move(bool);
	virtual void shoot();
};

