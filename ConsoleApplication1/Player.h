#pragma once
#include "Ship.h"
#include "SFML/Graphics.hpp"

class Player :
	public Ship
{
public:
	Player(sf::RenderWindow *);
	~Player();

	virtual bool move(bool);
	virtual void shoot();
};

