#include "Globals.h"
#include "Main_window.h"
#include <thread>

void renderingThread(Main_window* _window);

int main()
{
	// Main's variables
	Main_window window(sf::VideoMode(WINDOW_WIDTH + INFOS_SIZE, WINDOW_WIDTH),	"Jeu de Go");

#ifdef _WIN32
	// disable window's context
	window.setActive(false);

	// Launch thread
	sf::Thread thread_rendering(&renderingThread, &window);
	thread_rendering.launch();
#else
	//window.setFramerateLimit(300);
	window.setActive(false);
	std::thread thread_rendering(renderingThread, &window);
#endif

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
			case sf::Event::MouseWheelScrolled:
				window.zoom(event.mouseWheelScroll.delta, sf::Mouse::getPosition(window));
				break;
			case sf::Event::KeyPressed:
				window.keyPressed(event.key);
				break;
			default:
				break;
			}
		}

		// Treate real-time actions


		// Linux version
#ifndef _WIN32
		// Clear the window with a black screen
		window.clear(sf::Color::Black);

		// Draw everything here
		window.draw();

		// End of current frame, display everything
		window.display();
#endif

	}

	// Wait for the rendering thread has finished its instructions before exit
#ifdef _WIN32
	thread_rendering.wait();
#else
	thread_rendering.join();
#endif

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
