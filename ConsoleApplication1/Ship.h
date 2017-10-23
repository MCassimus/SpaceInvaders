#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Bullet.h"

class Ship : public GameObject
{
public:
	Ship(sf::RenderWindow *);
	virtual ~Ship();
	virtual bool move(int);
	virtual void update(std::vector<GameObject *>);
	virtual void update();
	virtual void render();
	bool shoot();
	int getLife() const;
	void takeLife();
	int getPoints() const;
	virtual void renderLives();
	std::vector<Animation *> animation;
protected:
	int lives = 1;
	int points = 0;
	Bullet * activeShot = nullptr;
};