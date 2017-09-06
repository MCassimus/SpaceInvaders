#pragma once
#include <SFML/Graphics.hpp>
#include "Bullet.h"
class Ship
{
public:
	Ship();
	~Ship();
	virtual bool move(bool) = 0;
	virtual void shoot() = 0;
protected:
	sf::Rect<int> rectangle;
	sf::RenderWindow * window;
	int lives = 1;
	int points;
	Bullet * activeShot = nullptr;
};

