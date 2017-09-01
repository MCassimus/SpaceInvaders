#pragma once
#include <SFML/Graphics.hpp>

class Bullet
{
public:
	Bullet(sf::Vector2i, sf::RenderWindow *);
	~Bullet();
	bool collide();
	void update();
	void render();
private: 
	sf::RectangleShape * rectangle;
	sf::Vector2f velocity = sf::Vector2f(0, 2);
	sf::RenderWindow * window;
};