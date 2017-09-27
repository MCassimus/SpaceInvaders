#pragma once
#include "GameObject.h"
#include "SFML\Graphics.hpp"
class Shield : public GameObject
{
public:
	Shield(int, sf::RenderWindow *);
	~Shield();
	void update();
	void takeHealth();
	int getHealth() const;
private:
	int health = 15;
};