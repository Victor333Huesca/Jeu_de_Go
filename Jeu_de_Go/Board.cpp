#include "Board.h"

Board::Board(sf::RenderWindow& _window) :
	size(),
	array(nullptr),
	window(_window),
	bg_txr(),
	bg_spr(),
	nextToPlay(Square::White)
{
	// Load background
	bg_txr.loadFromFile("./Img/background1.png");
	bg_spr.setTexture(bg_txr);
}





Board::~Board()
{
	
	for (size_t i = 0; i < size.x; i++)
	{
		delete[] array[i];
	}
	delete[] array;
}

void Board::click(sf::Vector2i pos, const sf::Mouse::Button & type)
{
	pos.x -= OFFSET_X;
	pos.y -= OFFSET_Y;
	if (pos.x >= 0 && 
		pos.y >= 0 && 
		pos.x + OFFSET_X < SIZE_X * SQUARE_SIZE + OFFSET_X &&
		pos.y + OFFSET_Y < SIZE_Y * SQUARE_SIZE + OFFSET_Y)
	{
		nextToPlay = type == sf::Mouse::Left ?
			Square::White :
			(type == sf::Mouse::Right ?
				Square::Black :
				Square::None);

		pos = getSquareAt(pos);
		array[pos.x][pos.y].setValue(nextToPlay);
		array[pos.x][pos.y].update();

	}
}

sf::Vector2i Board::getSquareAt(sf::Vector2i pos) const
{
	pos.x /= SQUARE_SIZE;
	pos.y /= SQUARE_SIZE;

	return pos;
}

sf::RenderWindow & Board::getWindow()
{
	return window;
}

void Board::draw()
{
	window.draw(bg_spr);
	for (size_t i = 0; i < size.x; i++)
	{
		for (size_t j = 0; j < size.y; j++)
		{
			array[i][j].draw(window);
		}
	}
}
