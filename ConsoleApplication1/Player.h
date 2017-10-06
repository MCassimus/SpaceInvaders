#pragma once
#include "Ship.h"
#include <SFML\Audio.hpp>

class Player :
	public Ship
{
public:
	Player(int, sf::RenderWindow*, char * = "Player 1");
	~Player();
	void update(std::vector<GameObject*>&);
	void update();
	bool move(int);
	void shoot();
	char * player = nullptr;
	int getScore() const;
	void renderLives();
private:
	unsigned int score = 0;
	unsigned int shotCount = 0;
	Ship * extraLives = nullptr;
	sf::SoundBuffer bulletBuffer;
	sf::Sound bulletSound;
	sf::SoundBuffer enemyDeathBuffer;
	sf::Sound enemyDeath;

};