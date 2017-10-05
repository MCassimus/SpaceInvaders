#include "stdafx.h"
#include "Word.h"
#include <iostream>
#include <string>


Word::Word(sf::RenderWindow *renderWindow, std::string str) : GameObject(renderWindow)
{
	text.setString(str);
	if (!font.loadFromFile("ArcadeFont.ttf"))
	{
		std::cout << "unable to load font" << std::endl;
		system("pause");
	}

	text.setFont(font);

	rectangle.setSize(sf::Vector2f(14,12));

	text.setCharacterSize(rectangle.getSize().x);

	sf::Vector2i halfTextSize(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
	text.setOrigin(sf::Vector2f(halfTextSize));

	window = renderWindow;
}


Word::~Word()
{
}


//draw word, have to change view size to make not-blurry
void Word::render()
{
	sf::View oldView = window->getView();
	window->setView(sf::View(sf::Rect<float>(0, 0, oldView.getSize().x*2,oldView.getSize().y*2)));
	window->draw(text);
	window->setView(oldView);
}

void Word::update()
{
	text.setPosition(rectangle.getPosition());
	text.setFillColor(rectangle.getFillColor());
	text.setCharacterSize(rectangle.getSize().x);
}

void Word::setTexture(std::string str)
{
	text.setString(str);
}
