#pragma once
#include "SFML\Graphics.hpp"
class Shield
{
public:
	Shield(sf::RenderWindow *);
	~Shield();
	void update();
	void render();
private:
	sf::RenderWindow * window;
	sf::RectangleShape rectangle;
	sf::Texture texture;
};