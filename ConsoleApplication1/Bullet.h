#pragma once
#include "GameObject.h"
#include <SFML\Audio.hpp>

class Bullet : public GameObject
{
public:
	Bullet(sf::Vector2i, sf::RenderWindow *);
	~Bullet();
	void update();
	void setVelocity(sf::Vector2f);
	bool offScreen();
private:
	sf::Vector2f velocity = sf::Vector2f(0, 1);
	int textureScale = 1;
	int flipTick = 1;
};