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
<<<<<<< HEAD
	void setPosition(sf::Vector2f);
	void setFillColor(sf::Color);
=======
	virtual std::string getTexture();
>>>>>>> 574fc9f39151f339e2034c683fb78f622ee5a535
protected:
	sf::RenderWindow *  window = nullptr;
	sf::RectangleShape rectangle;
	sf::Texture texture;
	std::string textureName = "default";
};