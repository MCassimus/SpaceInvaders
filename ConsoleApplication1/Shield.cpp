#include "stdafx.h"
#include "Shield.h"


Shield::Shield(sf::RenderWindow * renderWindow)
{
	window = renderWindow;
	texture.loadFromFile("../Textures/shield.png");
	rectangle = sf::RectangleShape(sf::Vector2f(400, 16));
	rectangle.setTexture(&texture);
	rectangle.setPosition(rectangle.getPosition().x, window->getSize().y - 100);
}


Shield::~Shield()
{
}


void Shield::update()
{
	return;
}


void Shield::render()
{
	window->draw(rectangle);
}