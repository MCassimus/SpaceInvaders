#include "stdafx.h"
#include "Animation.h"


Animation::Animation(sf::Vector2f pos, std::vector<std::string> frames, sf::RenderWindow * wndw): GameObject(wndw)
{
	frameFiles = frames;
	rectangle.setPosition(pos);
	update();
}

Animation::~Animation()
{
}

void Animation::update()
{

	if (frame < frameFiles.size() && frameDelay % 8 == 0)
	{
		setTexture(frameFiles.at(frame));
		frame++;
		frameDelay = 1;
	}
	else
		frameDelay++;
}

bool Animation::isDone()
{
	return frame >= frameFiles.size();
}
