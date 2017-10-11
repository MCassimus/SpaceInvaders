#pragma once
#include "GameObject.h"

class Shield : public GameObject
{
public:
	Shield(int, sf::RenderWindow *);
	void update();
	void takeHealth();
	int getHealth() const;
private:
	int health = 15;
};