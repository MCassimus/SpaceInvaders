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
	void setPosition(sf::Vector2f);
	void setFillColor(sf::Color);
	virtual std::string getTexture() const;
	sf::Vector2f getPosition();
protected:
	sf::RenderWindow *  window = nullptr;
	sf::RectangleShape rectangle;
	sf::Texture texture;
	std::string textureName = "default";
};