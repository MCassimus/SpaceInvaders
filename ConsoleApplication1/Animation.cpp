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
	if (frame < frameFiles.size())
	{
		setTexture(frameFiles.at(frame));
		frame++;
	}
}

bool Animation::isDone()
{
	return frame >= frameFiles.size();
}
