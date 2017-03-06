#include "Globals.h"
#include <thread>
#include "Screens.h"
#include "Game/Game_window.h"

#define	MULTITHREAD false

void renderingThread(sf::RenderWindow* _window, std::vector<Screen*>* _screens, int* _cur_screen);


int main()
{
	// Main's variables
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH + INFOS_SIZE, WINDOW_WIDTH),	"Jeu de Go");
    std::vector<Screen*> screens;
    int cur_screen = 0;

	// Declare here different screens in order of there use.
	screens.push_back(new Game_window);

#if defined(_WIN32) || MULTITHREAD
	// disable window's context
	window.setActive(false);

	// Launch thread
	std::thread thread_rendering(renderingThread, &window, &screens, &cur_screen);
#endif

	window.setFramerateLimit(300);

	//Main loop
	while (cur_screen >= 0)
	{
		cur_screen = screens[cur_screen]->Run(window);
	}

	// Wait for the rendering thread has finished its instructions before exit
#if defined(_WIN32) || MULTITHREAD
	thread_rendering.join();
#endif

	// Free screens
	for (auto sc : screens)
	{
		delete sc;
	}
	screens.clear();

	return 0;
}

void renderingThread(sf::RenderWindow* _window, std::vector<Screen*>* _screens, int* _cur_screen)
{
	// Get the render window
	sf::RenderWindow& window = *_window;
	std::vector<Screen*>& screens = *_screens;
	int& cur_screen = *_cur_screen;

	while (cur_screen >= 0)
	{
		// Clear the window with a black screen
		window.clear(sf::Color::Black);

		// Draw everything here
		window.draw(*screens[cur_screen]);

		// End of current frame, display everything
		window.display();
	}
}
