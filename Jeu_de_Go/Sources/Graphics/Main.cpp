#include "Globals.h"
#include <thread>
#include "Screens.h"
#include "../Engine/Parser.h"
#include "Menu_simple.h"
#include "Menu_Miniature.h"
#include "Choice_miniature.h"
#include "Choice_Simple.h"
#include "Game/Game_window.h"
#include <fstream>
#include <cassert>
#include "Go_Solver.h"

#define	MULTITHREAD false

void renderingThread(sf::RenderWindow* _window, const std::vector<Screen*>* _screens, const Screens* _cur_screen);

// A déplacer en méthode de Goban (sauf le test évidement)
uint8_t* compressGoban(const Goban& goban, int nb_revelent = 0);
void uncompressGoban(const uint8_t* compressed, const Etat::VAL KO_status, Goban& goban, int nb_revelent = 0);
void test();

extern std::ofstream log_file("trace.log");

int main()
{
	// Create the window
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH + INFOS_SIZE, WINDOW_HEIGHT), "Jeu de Go");

	// Create a solver applic witch contain all informations about the game
	Go_Solver* solver = new Go_Solver();
	
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

uint8_t* compressGoban(const Goban& goban, int nb_revelent)
{
	const short unsigned used_bits = 2;	// Has to be a power of 2 lower than 8.

	// Firstly just count numher on revelent intersections if the user doesn't specify it
	if (!nb_revelent)
	{
		for (int i = 0; i < TGOBAN; i++)
		{
			for (int j = 0; j < TGOBAN; j++)
			{
				switch (goban.coord(i, j).getVal())
				{
				case Etat::VAL::BLANC:
				case Etat::VAL::NOIR:
				case Etat::VAL::VIDE:
				case Etat::VAL::KOBLACK:
				case Etat::VAL::KOWHITE:
					// The intersection has to be compressed in all these cases
					nb_revelent += used_bits;
					break;

				default:
					break;
				}
			}
		}
	}

	// So start compression now
	int nb_bytes = (int)ceil(nb_revelent / 8.f);			// 90.25 --> 91
	int nb_wasted_bits = 8 - nb_revelent % 8;		// 8 - 2  --> 6
	uint8_t* compressed = new uint8_t[nb_bytes];

	int current = 0;
	short int buff_used = 0;

	enum Codes : uint8_t { empty = 0, black = 1, white = 2, KO = 3 };

	for (int i = 0; i < TGOBAN; i++)
	{
		for (int j = 0; j < TGOBAN; j++)
		{
			switch (goban.coord(i, j).getVal())
			{
			case Etat::VAL::BLANC:
				compressed[current] <<= used_bits;
				compressed[current] += Codes::white;
				buff_used += used_bits;
				break;

			case Etat::VAL::NOIR:
				compressed[current] <<= used_bits;
				compressed[current] += Codes::black;
				buff_used += used_bits;
				break;

			case Etat::VAL::VIDE:
				compressed[current] <<= used_bits;
				compressed[current] += Codes::empty;
				buff_used += used_bits;
				break;

			case Etat::VAL::KOBLACK:
			case Etat::VAL::KOWHITE:
				compressed[current] <<= used_bits;
				compressed[current] += Codes::KO;
				buff_used += used_bits;
				break;

			default:
				break;
			}

			if (buff_used == 8)
			{
				current++;
				buff_used = 0;
			}
		}
	}

	// Remplir le vide;
	compressed[nb_bytes - 1] <<= nb_wasted_bits;

	return compressed;
}

void uncompressGoban(const uint8_t* compressed, const Etat::VAL KO_status, Goban& goban, int nb_revelent)
{
	const short unsigned used_bits = 2;	// Has to be a power of 2 lower than 8.

	// Firstly just count numher on revelent intersections if the user doesn't specify it
	if (!nb_revelent)
	{
		for (int i = 0; i < TGOBAN; i++)
		{
			for (int j = 0; j < TGOBAN; j++)
			{
				switch (goban.coord(i, j).getVal())
				{
				case Etat::VAL::VIDE:
				case Etat::VAL::BLANC:
				case Etat::VAL::NOIR:
				case Etat::VAL::KOBLACK:
				case Etat::VAL::KOWHITE:
					// The intersection has to be compressed in all these cases
					nb_revelent += used_bits;
					break;

				default:
					break;
				}
			}
		}
	}

	int nb_bytes = (int)ceil(nb_revelent / 8.f);			// 90.25 --> 91
	int nb_wasted_bits = 8 - nb_revelent % 8;		// 8 - 2  --> 6

	// Start looking at the first place of the goban so -1 avoid skipping this first location.
	int current = -1;

	uint8_t masque = ~0;
	masque <<= (8 - used_bits);

	enum Codes : uint8_t { empty = 0, black = 1, white = 2, KO = 3 };

	// Read each byte untill last which contain waste
	for (int i = 0; i < nb_bytes - 1; i++)
	{
		// Read current
		int current_byte = compressed[i];

		for (int j = 0; j < 8; j += used_bits)
		{
			// Read bits
			int _tmp = (current_byte & masque) >> (8 - used_bits);
			current_byte <<= used_bits;
			assert(_tmp <= 3 && _tmp >= 0);				// Check that read value is correct
			Codes tmp = (Codes)_tmp;

			// Seach next available location in the goban
			do
			{
				current++;
			} while (goban[current].getVal() != Etat::VAL::VIDE &&
				goban[current].getVal() != Etat::VAL::BLANC &&
				goban[current].getVal() != Etat::VAL::NOIR &&
				goban[current].getVal() != Etat::VAL::KOBLACK &&
				goban[current].getVal() != Etat::VAL::KOWHITE);

			// Start interpreting
			switch (tmp)
			{
			case Codes::white:
				goban[current].setVal(Etat::VAL::BLANC);
				break;
			case Codes::black:
				goban[current].setVal(Etat::VAL::NOIR);
				break;
			case Codes::empty:
				goban[current].setVal(Etat::VAL::VIDE);
				break;
			case Codes::KO:
				goban[current].setVal(KO_status);
				break;
			default:
				std::cerr << "Error : Wrong Code readed \"" << tmp << "\" !" << std::endl;
				exit(-1);
				break;
			}
		}
	}

	// Read last byte
	int current_byte = compressed[nb_bytes - 1];
	for (int i = 0; i < 8 - nb_wasted_bits; i += used_bits)
	{
		// Read bits
		int _tmp = (current_byte & masque);
		current_byte <<= used_bits;
		assert(_tmp <= 3 && _tmp >= 0);				// Check that read value is correct
		Codes tmp = (Codes)_tmp;

		// Seach next available location in the goban
		do
		{
			current++;
		} while (goban[current].getVal() != Etat::VAL::VIDE &&
			goban[current].getVal() != Etat::VAL::BLANC &&
			goban[current].getVal() != Etat::VAL::NOIR &&
			goban[current].getVal() != Etat::VAL::KOBLACK &&
			goban[current].getVal() != Etat::VAL::KOWHITE);

		// Start interpreting
		switch (tmp)
		{
		case Codes::white:
			goban[current].setVal(Etat::VAL::BLANC);
			break;
		case Codes::black:
			goban[current].setVal(Etat::VAL::NOIR);
			break;
		case Codes::empty:
			goban[current].setVal(Etat::VAL::VIDE);
			break;
		case Codes::KO:
			goban[current].setVal(KO_status);
			break;
		default:
			std::cerr << "Error : Wrong Code readed \"" << tmp << "\" !" << std::endl;
			exit(-1);
			break;
		}
	}
}

void test()
{
	// Write a goban
	Goban goban;
	for (int i = 0; i < TGOBAN; i++)
	{
		for (int j = 0; j < TGOBAN; j++)
		{
			if ((i + j) % 7 == 0)
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
	uint8_t* comp = compressGoban(goban);
	for (int i = 0; i < ceil((TGOBAN * TGOBAN) / 4 + 1); i++)
	{
		out << comp[i];
	}
	out.close();


	// Uncompress
	Goban uncomp;
	uncompressGoban(comp, Etat::VAL::KOBLACK, uncomp);
	std::cout << "\n" << uncomp << std::endl;
}
