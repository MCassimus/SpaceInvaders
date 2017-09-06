#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>

class Bullet : public GameObject
{
public:
	Bullet(sf::Vector2i, sf::RenderWindow *);
	~Bullet();
};