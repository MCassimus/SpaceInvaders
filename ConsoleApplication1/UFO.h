#pragma once
#include "Ship.h"
#include <SFML\Audio.hpp>

class UFO : public Ship
{
public:
	UFO(sf::RenderWindow *);
	virtual ~UFO();
	bool move(int);
	bool shoot();
	virtual void update();
	void actuallyDie();
	bool actuallyDead();
private:
	int direction;
	sf::SoundBuffer buffer;
	sf::Sound ufoSound;
	bool permDeath;
};