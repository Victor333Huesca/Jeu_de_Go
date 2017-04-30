#pragma once
#include "../Globals.h"
#include "../../Engine/Etat.h"

class Square : sf::Drawable
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

	// Initialisation of textures
	static void loadTextures();

	// Accesors for Square's position - Write is private 'cause it's initialise then never touch again
	void setPosition(const sf::Vector2f position);

	// Used to change square's value
	void setValue(const Value& val);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;

private:
	// Attributes
	Value value;
	static sf::Texture white_t;
	static sf::Texture black_t;
	sf::Sprite sprite;
};
