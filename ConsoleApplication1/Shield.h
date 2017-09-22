#pragma once
#include "GameObject.h"
#include "SFML\Graphics.hpp"
class Shield : public GameObject
{
public:
	Shield(sf::RenderWindow *);
	~Shield();
	void update();
	void takeHealth();
private:
	int health = 15;
};