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

int Game_window::Run(sf::RenderWindow &window)
{
	// To stay alive
	bool Running = true;

	while (Running)
	{
		// Look each event
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Differents event type
			switch (event.type)
			{
			case sf::Event::Closed:
				return -1;
				break;
			case sf::Event::LostFocus:
				break;
			case sf::Event::GainedFocus:
				break;
			case sf::Event::MouseButtonReleased:
				click(window, sf::Mouse::getPosition(window), event.mouseButton.button);
				break;
			case sf::Event::MouseWheelScrolled:
				zoom(event.mouseWheelScroll.delta, sf::Mouse::getPosition(window), window);
				break;
			case sf::Event::KeyPressed:
				keyPressed(event.key);
				break;
			default:
				break;
			}
		}

		// Treate real-time actions

		// Linux version
#if !defined(_WIN32) && !MULTITHREAD
		// Clear the window with a black screen
		window.clear(sf::Color::Black);

		// Draw everything here
		window.draw(*this);

		// End of current frame, display everything
		window.display();
#endif
	}


	// Not suppose to reach here but just in case
	return -1;
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
	if (key.control)
	{
		// Ctrl + ...
		if (key.code == sf::Keyboard::Z)
		{
			// Ctrl + Z
			board.cancel();
		}
		else if (key.code == sf::Keyboard::Y)
		{
			// Ctrl + Y
			// It will be more complecated than I expected.
			size_t choix;
			std::cout << "_______________Parser v1.1 (console)________________ " << std::endl;
			std::cout << "Problème disponible (3) : " << std::endl;
			std::cout << "Veuillez choisir votre problème : ";
			std::cin >> choix;
			for (size_t x = 0; x < TGOBAN; x++)
			{
				for (size_t y = 0; y < TGOBAN; y++)
				{
					board.engine.coord(x, y).setVal(Etat::VIDE);
				}
			}
			board.load();
			for (size_t x = 9; x < TGOBAN; x++)
			{
				for (size_t y = 7; y < TGOBAN; y++)
				{
					board.engine.coord(x, y).setVal(Etat::NJ);
				}
			}
			switch (choix)
			{
			case 1:
				board.engine.coord(1, 3).setVal(Etat::NOIR);
				board.engine.coord(2, 3).setVal(Etat::NOIR);
				board.engine.coord(3, 3).setVal(Etat::NOIR);
				board.engine.coord(4, 3).setVal(Etat::NOIR);
				board.engine.coord(5, 3).setVal(Etat::NOIR);
				board.engine.coord(6, 3).setVal(Etat::NOIR);
				board.engine.coord(6, 2).setVal(Etat::NOIR);
				board.engine.coord(6, 1).setVal(Etat::NOIR);
				board.engine.coord(1, 5).setVal(Etat::NOIR);
				board.engine.coord(1, 2).setVal(Etat::BLANC);
				board.engine.coord(2, 2).setVal(Etat::BLANC);
				board.engine.coord(3, 2).setVal(Etat::BLANC);
				board.engine.coord(4, 2).setVal(Etat::BLANC);
				board.engine.coord(5, 2).setVal(Etat::BLANC);
				break;
			case 2: 
				board.engine.coord(3, 1).setVal(Etat::NOIR);
				board.engine.coord(4, 1).setVal(Etat::NOIR);
				board.engine.coord(6, 1).setVal(Etat::NOIR);
				board.engine.coord(7, 1).setVal(Etat::NOIR);
				board.engine.coord(4, 2).setVal(Etat::NOIR);
				board.engine.coord(6, 2).setVal(Etat::NOIR);
				board.engine.coord(5, 3).setVal(Etat::NOIR);
				board.engine.coord(6, 3).setVal(Etat::NOIR);
				board.engine.coord(3, 0).setVal(Etat:);
				board.engine.coord(2, 1).setVal(Etat::BLANC);
				board.engine.coord(8, 1).setVal(Etat::BLANC);
				board.engine.coord(3, 2).setVal(Etat::BLANC);
				board.engine.coord(4, 2).setVal(Etat::BLANC);
				board.engine.coord(4, 3).setVal(Etat::BLANC);
				board.engine.coord(5, 3).setVal(Etat::BLANC);
				board.engine.coord(6, 4).setVal(Etat::BLANC);
				board.engine.coord(6, 5).setVal(Etat::BLANC);
				board.engine.coord(6, 6).setVal(Etat::BLANC);
				break;
			case 3: 
				break;
			}
			

			board.load();
			

		}
	}
	else
	{
		// Not Ctrl
	}
}
