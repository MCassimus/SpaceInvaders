#pragma once
#include <SFML\Graphics.hpp>
class GameObject
{
public:
	GameObject(sf::RenderWindow *);
	~GameObject();
	void render();
	void update();
	bool collide(GameObject *);
	void setTexture(std::string);
protected:
	sf::RenderWindow *  window = nullptr;
	sf::RectangleShape rectangle;
};