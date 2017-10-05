#pragma once
#include "GameObject.h"
class Word :
	public GameObject
{
public:
	Word(sf::RenderWindow *, std::string str);
	~Word();
	void render();
	void update();//makes text copy rectangle
	void setTexture(std::string);//changes string
private:
	sf::Text text;
	sf::Font font;
};

