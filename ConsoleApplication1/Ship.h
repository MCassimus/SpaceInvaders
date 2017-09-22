#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include "Bullet.h"
class Ship : public GameObject
{
public:
	Ship(sf::RenderWindow *);
	~Ship();
	virtual bool move(int);
	virtual void update(std::vector<GameObject *>);
	void update();
	void render();
	bool shoot();
	int getLife() const;
	void takeLife();
	int getPoints() const;
protected:
	int lives = 1;
	int points = 0;
	Bullet * activeShot = nullptr;
};