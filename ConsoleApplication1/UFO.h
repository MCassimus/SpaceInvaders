#pragma once
#include "Ship.h"
#include <SFML\Audio.hpp>

class UFO : public Ship
{
public:
	UFO(sf::RenderWindow *);
	~UFO();
	bool move(int);
	bool shoot();
	void update();
private:
	int direction;
	sf::SoundBuffer buffer;
	sf::Sound ufoSound;
};