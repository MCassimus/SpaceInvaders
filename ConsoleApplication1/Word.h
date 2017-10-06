#pragma once
#include "GameObject.h"

class Word :
	public GameObject
{
public:
	Word(sf::RenderWindow *, std::string str, float = 14);
	~Word();
	void render();
	void update();//makes text copy rectangle
	void setTexture(std::string);//changes string
	void setPosition(sf::Vector2f);
	void setCharacterSize(float);
private:
	sf::Text text;
	sf::Font font;
};