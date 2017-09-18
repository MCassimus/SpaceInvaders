#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>

class Bullet : public GameObject
{
public:
	Bullet(sf::Vector2i, sf::RenderWindow *);
	~Bullet();
	void update();
	void setVelocity(sf::Vector2f);
	bool offScreen();	
private:
	sf::Vector2f velocity = sf::Vector2f(0, 2);
};