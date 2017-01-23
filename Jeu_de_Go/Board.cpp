#include "Board.h"

Board::Board(sf::RenderWindow& _window) :
	size(),
	array(nullptr),
	window(_window),
	bg_txr(),
	bg_spr()
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
