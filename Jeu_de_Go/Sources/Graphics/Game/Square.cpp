#include "Square.h"

sf::Texture Square::white_t;
sf::Texture Square::black_t;
sf::Texture Square::unplayable_t;

Square::Square(const sf::Vector2i position, Value _value) :
	value(_value),
	sprite()
{
	// Set position of the square
	setPosition(static_cast<sf::Vector2f>(position));

	// Set its sprite
	setValue(_value);
}

Square::~Square()
{
}

void Square::loadTextures()
{
	white_t.loadFromFile("./Ressources/Img/Others/stone_white3.png");
	black_t.loadFromFile("./Ressources/Img/Others/stone_black3.png");
	unplayable_t.loadFromFile("./Ressources/Img/Others/stone_unplayable.png");

	//white_t.setSmooth(true);
	//black_t.setSmooth(true);
}

void Square::setPosition(const sf::Vector2f position)
{
	if (position != sf::Vector2f(-1, -1))
	{
		sprite.setPosition(
			position.x * SQUARE_WIDTH + OFFSET_X_B + VIEW_BOARD_POS_X,
			position.y * SQUARE_HEIGHT + OFFSET_Y_B + VIEW_BOARD_POS_Y);
	}
}

void Square::setValue(const Value & val)
{
	// Set the value
	value = val;

	// Load right texture
	if (value == Black)
		sprite.setTexture(black_t);
	else if (value == White)
		sprite.setTexture(white_t);
	else if (value == Unplayable)
		sprite.setTexture(unplayable_t);
	else
		;//std::cerr << "Etat de Square Inconu !" << std::endl;
}

void Square::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (value == Unplayable && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl))
		return;
	if (value != None)
		target.draw(sprite, states);
}
