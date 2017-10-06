#pragma once
#include "GameObject.h"

class Animation : public GameObject
{
public:
	Animation(sf::Vector2f, std::vector<std::string>, sf::RenderWindow *);
	~Animation();
	void update();
	bool isDone();
	bool move(int);
private:
	int frame = 0;
	int frameDelay = 1;
	std::vector<std::string> frameFiles;
};