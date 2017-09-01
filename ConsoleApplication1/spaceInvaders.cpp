/*
	Michael Cassimus / Daniel Barnett
	Space Invaders
	Recreate arcade game space invaders
*/
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "Bullet.h"

void loop(int &, sf::RenderWindow &);
void render(sf::RenderWindow &);


int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "Space Invaders");
	int score = 0;
	
	window.setFramerateLimit(60);
	
	while (window.isOpen())
	{
		loop(score, window);
		render(window);
	}

	return 0;
}


void loop(int & score, sf::RenderWindow & window)
{
	Bullet * bullet = nullptr;
	#pragma region event
	// Process events
	sf::Event event;
	while (window.pollEvent(event))
	{
		// Close window: exit
		if (event.type == sf::Event::Closed)
			window.close();
		else if (event.type == sf::Event::KeyPressed)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		}
	}	
	#pragma endregion

	return;
}


void render(sf::RenderWindow & window)
{	
	window.clear();

	//draw objects

	window.display();
}