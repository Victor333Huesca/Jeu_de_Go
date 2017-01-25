#include "Square.h"


Square::Square(const sf::Vector2i position, Value _value) :
	value(_value)
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

void Square::update()
{
	updateTexture();
	updateSprite();
}

sf::Vector2f Square::getPosition() const
{
	return sprite.getPosition();
}

void Square::setPosition(const sf::Vector2f position)
{
	sprite.setPosition(
		position.x * texture.getSize().x + OFFSET_X,
		position.y * texture.getSize().y + OFFSET_Y);
}

void Square::setValue(const Value & val)
{
	value = val;
}

void Square::draw(sf::RenderWindow & window) const
{
	window.draw(sprite);
}
