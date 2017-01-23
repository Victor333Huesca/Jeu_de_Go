#include "Square.h"


Square::Square(const sf::Vector2i position, Value _value) :
	value(_value),
	allowed(true)
{
	// Set position of the square
	setPosition(static_cast<sf::Vector2f>(position));

	// Set it's sprite
	updateSprite();
}

Square::~Square()
{
}

void Square::updateTexture()
{
	// File name
	std::string name("./Img/");

	// Load write filename
	switch (value)
	{
	case Black:
		name.append("stone_black");
		break;

	case White:
		name.append("stone_white");
		break;

	case None:
		name.append("blank");
		break;

	default:
		break;
	}

	// Add extention
	name.append(".png");

	// Load file
	texture.loadFromFile(name);
}

void Square::updateSprite()
{
	updateTexture();
	sprite.setTexture(texture);
}

sf::Vector2f Square::getPosition() const
{
	return sprite.getPosition();
}

void Square::setPosition(const sf::Vector2f position)
{
	sprite.setPosition(position.x * texture.getSize().x, position.y * texture.getSize().y);
}

void Square::draw(sf::RenderWindow & window) const
{
	window.draw(sprite);
	std::cout << "Position : (" << sprite.getPosition().x << ", " << sprite.getPosition().y << ")\n";
	std::cout << "Color : " << value << "\n";
}
