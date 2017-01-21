#include "Board.h"



Board::Board(sf::RenderWindow& window) :
	array(nullptr),
	board_window(window)
{
}


Board::~Board()
{
	for (size_t i = 0; i < size.x; i++)
	{
		delete[] array[i];
	}
	delete[] array;
}

