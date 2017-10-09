#include "stdafx.h"
#include <string>
#include "Word.h"


Word::Word(sf::RenderWindow *renderWindow, std::string str, float textSize) : GameObject(renderWindow)
{
	text.setString(str);
	if (!font.loadFromFile("Pixel-Miners.otf"))
	{
		std::printf("Unable to load font.\n");
		system("pause");
	}

	text.setFont(font);

	rectangle.setSize(sf::Vector2f(textSize,12));

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

	text.setCharacterSize(rectangle.getSize().x);

	sf::Vector2i halfTextSize(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
	text.setOrigin(sf::Vector2f(halfTextSize));
}


void Word::setTexture(std::string str)
{
	text.setString(str);
}


void Word::setPosition(sf::Vector2f pos)
{
	rectangle.setPosition(pos);
}


void Word::setCharacterSize(float size)
{
	rectangle.setSize(sf::Vector2f(rectangle.getSize().x, size));
}