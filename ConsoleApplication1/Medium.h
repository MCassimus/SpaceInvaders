#pragma once
#include "Ship.h"
class Medium :
	public Ship
{
public:
	Medium(int, sf::RenderWindow*);
	~Medium();
	void render();
	void update();
	void move(bool);
	void shoot();
};