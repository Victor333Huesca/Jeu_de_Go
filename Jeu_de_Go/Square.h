#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>

#define SQUARE_SIZE 150
#define SIZE_X 19
#define SIZE_Y 19
#define OFFSET_X 80
#define OFFSET_Y 80

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
	void update();

	// Accesors for Square's position - Read only 'cause it's a constant
	sf::Vector2f getPosition() const;
	// Accesors for Square's position - Write is private 'cause it's initialise then never touch again
	void setPosition(const sf::Vector2f position);

	void setValue(const Value& val);

	void draw(sf::RenderWindow& window) const;

private:
	// Attributes
	Value value;
	sf::Texture texture;
	sf::Sprite sprite;
};

