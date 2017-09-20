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
	void update();
	void render();
	virtual void shoot() = 0;
	int getLife() const;
	void takeLife();
protected:
	int lives = 1;
	int points;
	Bullet * activeShot = nullptr;
};