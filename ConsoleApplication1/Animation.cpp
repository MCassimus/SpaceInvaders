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


bool Animation::move(int dir)
{
	sf::Vector2f position = rectangle.getPosition();
	if(!isDone())
	{
		if (dir == 0)
		{
			position.y += 8;
			rectangle.setPosition(position);
		}
		else if (dir == 1)
		{
			position.x += 2;
			rectangle.setPosition(position);
			if (position.x >= window->getView().getSize().x - 6)
				return true;
		}
		else
		{
			position.x -= 2;
			rectangle.setPosition(position);
			if (position.x <= 6)
				return true;
		}
	}
	else
	{
		position.y = window->getView().getSize().y;
		rectangle.setPosition(position);
	}
	return false;
}
