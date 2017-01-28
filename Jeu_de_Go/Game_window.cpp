#include "Game_window.h"



Game_window::Game_window() :
	board(sf::Vector2u(NB_SQUARES_X, NB_SQUARES_Y)),
	infos(),
	cur_player()
{
}


Game_window::~Game_window()
{
}

void Game_window::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	// Save current view
	sf::View cur_view(target.getView());

	// Draw board
	target.setView(board.getView());
	target.draw(board, states);

	// Draw Infos Menu
	target.setView(infos.getView());
	target.draw(infos, states);

	// Set back previous view
	target.setView(cur_view);
}

void Game_window::click(sf::RenderWindow & window, sf::Vector2i pos, const sf::Mouse::Button & type)
{
	// Get relative position
	pos = static_cast<sf::Vector2i>(window.mapPixelToCoords(pos, board.getView()));

	// Check that user has clicked on the board	
	if (pos.x >= OFFSET_X_B &&
		pos.y >= OFFSET_Y_B &&
		pos.x < NB_SQUARES_X * SQUARE_WIDTH + OFFSET_X_B &&
		pos.y < NB_SQUARES_Y * SQUARE_HEIGHT + OFFSET_Y_B)
	{
		board.click(pos, cur_player);
		cur_player =
			cur_player == Square::Value::Black ?
			Square::Value::White :
			Square::Value::Black;
	}
	else
	{
	}
}
