//#ifdef __MINGW32__
//#include "mingw.thread.h"
//#else
#include <thread>
//#endif // __MINGW32__
#include <fstream>
#include <cassert>
#include <cmath>
#include "Globals.h"
#include "Go_Solver.h"

#define	MULTITHREAD false

void renderingThread(sf::RenderWindow* _window, const std::vector<Screen*>* _screens, const Screens* _cur_screen);

// Permet de tester si la compression/decompression fonctionne
void test();

std::ofstream log_file("trace.log");


int main()
{
    /* ------ Tests ------ */
    //system(std::string("mkdir " + path).c_str());
	//std::ofstream file(std::string(path + ".log"));
    /* --- End of Tests --- */

    // Log file first
    //log_file.open("trace.log");

	// Create the window
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH + INFOS_SIZE, WINDOW_HEIGHT), "Jeu de Go");
	window.setVerticalSyncEnabled(false);

	// Create a solver app witch contain all informations about the game
	Go_Solver* solver = new Go_Solver();

	// Test a supprimer d'ici
	//test();
	// Din du test

	// Limit the framerate
	window.setFramerateLimit(60);

#if defined(_WIN32) || MULTITHREAD
	// disable window's context
	window.setActive(false);

	// Launch thread
	std::thread thread_rendering(renderingThread, &window, &solver->getScreens(), &solver->getScreen());
#endif

	// Start the program
	solver->Run(window);

	/* ----- Here the program is over -----
				start free memory
	   -----  close chat need to be   ----- */

	// Wait for the rendering thread has finished its instructions before exit
#if defined(_WIN32) || MULTITHREAD
	thread_rendering.join();
#endif

	// Close window & cie
	window.close();
	log_file.close();
	delete solver;

	return 0;
}

// Render
void renderingThread(sf::RenderWindow* _window, const std::vector<Screen*>* _screens, const Screens* _cur_screen)
{
	// Get the render window
	sf::RenderWindow& window = *_window;
	const std::vector<Screen*>& screens = *_screens;
	const Screens& cur_screen = *_cur_screen;

	while (cur_screen >= CONTINUE)
	{
		// Clear the window with a black screen
		window.clear(sf::Color::Black);

		// Draw everything here
		window.draw(*(screens[cur_screen]));

		// End of current frame, display everything
		window.display();
	}
}

void test()
{
	// Write a goban
	Goban goban;
	for (size_t i = 0; i < TGOBAN; i++)
	{
		for (size_t j = 0; j < TGOBAN; j++)
		{
			if (i > 8 || j > 5)
			{
				goban.coord(i, j).setVal(Etat::NJ);
			}
			else if ((i + j) % 7 == 0)
			{
				goban.coord(i, j).setVal(Etat::BLANC);
			}
			else if ((i + j + 3) % 7 == 0)
			{
				goban.coord(i, j).setVal(Etat::NOIR);
			}
			else if ((i + j) == 65)
			{
				goban.coord(i, j).setVal(Etat::VAL::KOBLACK);
			}
			else
			{
				goban.coord(i, j).setVal(Etat::VIDE);
			}
		}
	}

	std::cout << goban << std::endl;


	// Compress it
	std::ofstream out("./test.txt", std::ostream::out);
	uint8_t* comp = goban.compress();
	for (int i = 0; i < ceil((TGOBAN * TGOBAN) / 4 + 1); i++)
	{
		out << comp[i];
	}
	out.close();


	// Uncompress
	Goban uncomp;
	for (size_t i = 0; i < TGOBAN; i++)
	{
		for (size_t j = 0; j < TGOBAN; j++)
		{
			if (i > 8 || j > 5)
			{
				uncomp.coord(i, j).setVal(Etat::NJ);
			}
		}
	}
	uncomp.uncompress(comp, Etat::VAL::KOBLACK);
	std::cout << "\n" << uncomp << std::endl;
}
