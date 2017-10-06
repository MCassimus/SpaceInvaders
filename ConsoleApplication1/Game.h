#pragma once
#include "GameObject.h"
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

class Game
{
public:
	Game(sf::RenderWindow *, bool = false);
	~Game();
	bool loop();
	void render();
	void processKeyboard();
	void playerShoot(sf::Event);
private:
	sf::RenderWindow * window;
	std::vector<GameObject *> gameData[4];
	sf::RectangleShape lifeSeperator;
	int level;
	bool pause = false;
	sf::SoundBuffer sounds;
	sf::Sound soundPlayer;
};