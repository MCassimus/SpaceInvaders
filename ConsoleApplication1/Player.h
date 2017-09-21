#pragma once
#include "Ship.h"
class Player :
	public Ship
{
public:
	Player(int, sf::RenderWindow*, char * = "Player 1");
	~Player();
	void update(std::vector<GameObject*>);
	bool move(int);
	void shoot();
	char * player = nullptr;
	int getScore() const;
private:
	int score = 0;
};