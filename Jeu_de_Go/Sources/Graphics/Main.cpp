#include "Globals.h"
#include "Main_window.h"

void renderingThread(Main_window* _window);

int main()
{
	// Main's variables
	Main_window window(sf::VideoMode(WINDOW_WIDTH + INFOS_SIZE, WINDOW_WIDTH),	"Jeu de Go");

	// disable window's context
	window.setActive(false);

	// Launch thread
	sf::Thread thread_rendering(&renderingThread, &window);
	thread_rendering.launch();

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
				break;
			case sf::Event::GainedFocus:
				break;
			case sf::Event::MouseButtonReleased:
				window.click(sf::Mouse::getPosition(window), event.mouseButton.button);
				break;
			}
		}
	}

	// Wait for the rendering thread has finished its instructions before exit
	thread_rendering.wait();
	return 0;
}

void renderingThread(Main_window* _window)
{
	// Get the render window
	Main_window& window = *_window;
	window.setFramerateLimit(300);

	while (window.isOpen())
	{
		// Clear the window with a black screen
		window.clear(sf::Color::Black);

		// Draw everything here
		window.draw();

		// End of current frame, display everything
		window.display();
	}
}
