#include "stdafx.h"
#include "Word.h"
#include <iostream>


Word::Word(sf::RenderWindow *renderWindow, std::string str) : GameObject(renderWindow)
{
	text.setString(str);

	sf::Font font;
	if (!font.loadFromFile("Anisha Free.otf"))
	{
		std::cout << "unable to load font" << std::endl;
		system("pause");
	}

	text.setFont(font);

	window = renderWindow;
}


Word::~Word()
{
}

void Word::render()
{
	sf::Text newText = text;
	//window->draw(newText);
}

void Word::update()
{
	text.setPosition(rectangle.getPosition());
	text.setFillColor(rectangle.getFillColor());
	text.setCharacterSize(12);
}

void Word::setTexture(std::string str)
{
	text.setString(str);
}
