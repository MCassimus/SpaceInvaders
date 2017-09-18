#pragma once
#include <SFML\Graphics.hpp>
class GameObject
{
public:
	GameObject(sf::RenderWindow *);
	~GameObject();
	virtual void render();
	virtual void update() = 0;
	bool collide(GameObject *);
	virtual void setTexture(std::string);
protected:
	sf::RenderWindow *  window = nullptr;
	sf::RectangleShape rectangle;
	sf::Texture texture;
};