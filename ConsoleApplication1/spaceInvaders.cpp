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
	sf::RenderWindow window(sf::VideoMode(434, 496), "Space Invaders");
	window.setFramerateLimit(60);

	sf::View view(sf::Rect<float>(0, 0, 217, 248));
	window.setView(view);

	Game game(&window);
	
	while (game.loop())
		game.render();		
}