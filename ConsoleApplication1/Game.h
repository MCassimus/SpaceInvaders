#pragma once
#include <SFML\Graphics.hpp>
#include "Shield.h"
#include "Bullet.h"
//#include "Ship.h"
//#include "Player.h"
class Game
{
public:
	Game(sf::RenderWindow *);
	~Game();
	bool loop();
	void render();
	void processKeyboard();
private:
	sf::RenderWindow * window;
	//Enemy Ship Array
	//Ship enemies[][];
	//Player player1;//Player 1
	//Player player2;//Player 2 (if applicable)
	Shield * shield;
	sf::Font arcadeFont;
	sf::RectangleShape scorePrompt;
	sf::Texture scorePromptTexture;
	sf::Texture texture;
	sf::RectangleShape rectangle;
	Bullet * bullet = nullptr;
};