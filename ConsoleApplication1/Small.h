#pragma once
#include "Ship.h"
class Small :
	public Ship
{
public:
	Small(int,sf::RenderWindow*);
	~Small();
	void render();
	void update();
	void move(bool);
	void shoot();
};