#pragma once
#include <SFML/Graphics.hpp>
//#include "Ship.h"

class Bullet
{
public:
	Bullet(sf::Vector2i, sf::RenderWindow *);
	~Bullet();
	bool collide(/*Ship */);
	void update();
	void render();
	void setTexture(std::string);
private: 
	sf::RectangleShape rectangle;
	sf::Vector2f velocity = sf::Vector2f(0, -4);
	sf::RenderWindow * window;
};