#include <SFML/Graphics.hpp>
#include <iostream>
#include "Board.h"

#define TEST true

void renderingThread(Board* _board);

int main()
{
	// Creation of the render window
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");

	// Globals variables
	bool pause = false;
	//Board board(window);
	Board board(sf::Vector2u(5, 3), window);

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

	// Variables
	bool blink = true;

	// Create Shapes
	// Circle 1
	sf::CircleShape circle1(100);
	circle1.setFillColor(sf::Color::Green);
	// Square 1
	sf::RectangleShape square1(sf::Vector2f(100, 100));
	square1.setFillColor(sf::Color::Blue);

	while (window.isOpen())
	{
		// Clear the window with a black screen
		window.clear(sf::Color::Black);

		// Test here
		if (TEST)
			board.draw();

		// Draw everything which should be
		if (blink)
			window.draw(circle1);
		else
		{
			window.draw(square1);
		}
		blink = !blink;

		// End of current frame, display everything
		window.display();
		sf::sleep(sf::seconds(1));
	}
}