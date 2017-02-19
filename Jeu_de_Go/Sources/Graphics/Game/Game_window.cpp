#include "Game_window.h"



Game_window::Game_window() :
	board(sf::Vector2u(NB_SQUARES_X, NB_SQUARES_Y)),
	infos(),
	cur_player(Square::White)
{
	infos.setCurPlayer(Square::White);
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

void Game_window::click(const sf::RenderWindow & window, sf::Vector2i pos, const sf::Mouse::Button & type)
{
	// Test if mouse was in the board or the info menu
	if (pos.x <= WINDOW_WIDTH)
	{
		// Get relative position inside the board's view
		pos = static_cast<sf::Vector2i>(window.mapPixelToCoords(pos, board.getView()));

		// Test if value has been changed
		if (board.click(pos, cur_player, type))
		{
			// Change next player info
			cur_player =
				cur_player == Square::Value::Black ?
				Square::Value::White :
				Square::Value::Black;
			infos.setCurPlayer(cur_player);
		}
		else // Value didn't changed
		{

		}
	}
	else // Not the board so infos's menu
	{

	}
}

void Game_window::zoom(const float delta, sf::Vector2i pos, sf::RenderWindow& window)
{
	// Get relative position inside the board's view
	pos = static_cast<sf::Vector2i>(window.mapPixelToCoords(pos, board.getView()));

	// Look if the mouse is on the board
	board.zoom(delta, pos);
}

void Game_window::keyPressed(const sf::Event::KeyEvent & key)
{
	if (key.control && key.code == sf::Keyboard::Z)
	{
		// Ctrl + Z
		board.cancel();
	}
}
