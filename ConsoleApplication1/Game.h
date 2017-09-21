#pragma once
#include <SFML\Graphics.hpp>
#include "GameObject.h"
class Game
{
public:
	Game(sf::RenderWindow *, bool = false);
	~Game();
	bool loop();
	void render();
	void processKeyboard();
private:
	sf::RenderWindow * window;
	std::vector<GameObject *> gameData[3];
	sf::Font font;
	sf::Text player1Score;
	sf::Text player2Score;
};