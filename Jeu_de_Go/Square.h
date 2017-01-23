#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>

class Square
{
public:
	enum Value
	{
		Black,
		White,
		None
	};
	Square(const sf::Vector2i position = sf::Vector2i(-1, -1), Value _value = None);
	~Square();

	void updateTexture();
	void updateSprite();

	// Accesors for Square's position - Read only 'cause it's a constant
	sf::Vector2f getPosition() const;
	// Accesors for Square's position - Write is private 'cause it's initialise then never touch again
	void setPosition(const sf::Vector2f position);

	void draw(sf::RenderWindow& window) const;

private:
	// Attributes
	Value value;
	bool allowed;
	sf::Texture texture;
	sf::Sprite sprite;
};

