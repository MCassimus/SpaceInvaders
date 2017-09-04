/*
	Michael Cassimus / Daniel Barnett
	Space Invaders
	Recreate arcade game space invaders
*/
#include "stdafx.h"
#include <SFML\Graphics\RenderWindow.hpp>
#include "Game.h"


int main()
{
	sf::RenderWindow window(sf::VideoMode(400, 400), "Space Invaders");
	window.setFramerateLimit(60);

	Game game(&window);
	
	while (game.loop())
		game.render();		
}