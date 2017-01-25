#include <SFML/Graphics.hpp>
#include <iostream>
#include "Board.h"

void renderingThread(Board* _board);

int main()
{
	// Creation of the main view and the render window
	sf::View view(
		sf::FloatRect(
			0,
			0,
			SQUARE_SIZE * SIZE_X + OFFSET_X * 2,
			SQUARE_SIZE * SIZE_Y + OFFSET_Y * 2));
	sf::RenderWindow window(
		sf::VideoMode(
			800, 
			800), 
		"Jeu de Go !");
	window.setView(view);

	// Globals variables
	bool pause = false;
	//Board board(window);
	Board board(sf::Vector2u(SIZE_X, SIZE_Y), window);

	// disable context
	window.setActive(false);

	// Launch thread
	sf::Thread thread_rendering(renderingThread, &board);
	thread_rendering.launch() ;

	// Events loop
	while (window.isOpen())
	{
		// Look every event
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Differents event type
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::LostFocus:
				pause = true;
				break;
			case sf::Event::GainedFocus:
				pause = false;
				break;
			case sf::Event::MouseButtonReleased:
				board.click(
					static_cast<sf::Vector2i>(
						window.mapPixelToCoords(
							sf::Mouse::getPosition(window))),
					event.mouseButton.button);
				break;
			default:
				break;
			}
		}
	}

	return 0;
}

void renderingThread(Board* _board)
{
	// Get the render window
	Board& board = *_board;
	sf::RenderWindow& window = board.getWindow();

	while (window.isOpen())
	{
		// Clear the window with a black screen
		window.clear(sf::Color::Black);

		// Test here
		board.draw();

		// End of current frame, display everything
		window.display();
	}
}