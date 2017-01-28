#include "Board.h"

Board::Board() :
	size(),
	array(nullptr),
	bg_txr(),
	bg_spr(),
	view(sf::FloatRect(0, 0, 
		SQUARE_HEIGHT * NB_SQUARES_X + OFFSET_X_B + OFFSET_X_E,
		SQUARE_HEIGHT * NB_SQUARES_Y + OFFSET_Y_B + OFFSET_Y_E))
{
	// Initialise squares's textures
	Square::loadTextures();

	// Load background
	bg_txr.loadFromFile("./Img/background2.png");
	bg_spr.setTexture(bg_txr);

	// Set viewport
	view.setViewport(sf::FloatRect(0, 0, 1 - INFOS_SIZE, 1));
}

Board::~Board()
{
	for (size_t i = 0; i < size.x; i++)
	{
		delete[] array[i];
	}
	delete[] array;
}

void Board::click(sf::Vector2i pos, const Square::Value & value)
{
	// Get square at the position demanded
	pos = getSquareAt(pos);
	
	// Change square's value then update it
	array[pos.x][pos.y].setValue(value);
}

sf::View Board::getView() const
{
	return view;
}

sf::Vector2i Board::getSquareAt(sf::Vector2i pos) const
{
	pos.x /= SQUARE_HEIGHT;
	pos.y /= SQUARE_HEIGHT;

	return pos;
}

void Board::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(bg_spr);
	for (size_t i = 0; i < size.x; i++)
	{
		for (size_t j = 0; j < size.y; j++)
		{
			//target.draw(array[i][j], states);
			array[i][j].draw(target, states);
		}
	}
}
