#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include "Bullet.h"
class Ship : public GameObject
{
public:
	Ship(sf::RenderWindow *);
	~Ship();
	virtual bool move(bool) = 0;
	virtual void shoot() = 0;
protected:
	int lives = 1;
	int points;
	Bullet * activeShot = nullptr;
};