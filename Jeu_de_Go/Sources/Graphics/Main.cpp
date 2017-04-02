#include "Globals.h"
#include <thread>
#include "Screens.h"
#include "Menu.h"
#include "Game/Game_window.h"
#include <fstream>
#include <cassert>

#define	MULTITHREAD false

void renderingThread(sf::RenderWindow* _window, std::vector<Screen*>* _screens, int* _cur_screen);

// Différents menus
Menu* loadMenu1();

// A déplacer en méthode de Goban (sauf le test évidement)
uint8_t* compressGoban(const Goban& goban, int nb_revelent = 0);
void uncompressGoban(const uint8_t* compressed, const Etat::VAL KO_status, Goban& goban, int nb_revelent = 0);
void test();

int main()
{
	// Main's variables
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH + INFOS_SIZE, WINDOW_HEIGHT), "Jeu de Go");
    std::vector<Screen*> screens;
    int cur_screen = 1;

	// Declare here different screens in order of there use.
	screens.push_back(new Game_window);
	screens.push_back(loadMenu1());


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
	for (Screen*& sc : screens)
	{
		delete sc;
	}
	screens.clear();

	window.close();

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


Menu* loadMenu1()
{
	// On charge le menu
	Menu* menu = new Menu(sf::Vector2f(0, 0.f), "./Ressources/Img/Background3.png", "./Ressources/Font/time.ttf", sf::Vector2f(0.3f, 0.3f));

	// On charge le style du text sauf la police qui est incluse avec le menu.
	sf::Text text_style;
	text_style.setCharacterSize(50);
	text_style.setFillColor(sf::Color::Black);

	// Position
	sf::Vector2f pos(225, 125);// (WINDOW_WIDTH + INFOS_SIZE - (WINDOW_WIDTH + INFOS_SIZE) / 3.5) / 2, WINDOW_HEIGHT + 100);

	// On charge les items
	menu->addItem(Choice("        Jouer", text_style, pos.x, pos.y,	[](const sf::RenderTarget& window) 
	{ return 0; }));
	menu->addItem(Choice("       Options", text_style, pos.x, pos.y + 120, [](const sf::RenderTarget& window)
	{ return NO_CHANGE; }));
	menu->addItem(Choice("      Exemples", text_style, pos.x, pos.y + 240, [](const sf::RenderTarget& window)
	{ return NO_CHANGE; }));
	menu->addItem(Choice("      Problèmes", text_style, pos.x, pos.y + 360, [](const sf::RenderTarget& window)
	{ return NO_CHANGE; }));
	menu->addItem(Choice("       Quitter", text_style, pos.x, pos.y + 480, [](const sf::RenderTarget& window)
	{ return -1; }));

	// Then set items textures and return the menu
	menu->setItemsTextures("./Ressources/Img/button_blank.png", "./Ressources/Img/button_selected.png");
	
	std::cout << "Le Menu 1 à été chargé" << std::endl;

	return menu;

	/*
	sf::Text txt;
	sf::Font font;
	font.loadFromFile("./Ressources/Font/time.ttf");
	txt.setFont(font);
	txt.setString("Menu");
	txt.setCharacterSize(86);
	txt.setFillColor(sf::Color::Black);
	txt.setStyle(sf::Text::Bold);
	txt.setPosition(sf::Vector2f((WINDOW_WIDTH / 3.5) + 80, (WINDOW_HEIGHT / 4.5) - 80));


	t_background.loadFromFile("./Ressources/Img/background3.png");

	s_background.setTexture(t_background);

	s_background.setPosition(sf::Vector2f(0, 0));
	s_background.setScale(sf::Vector2f(0.3, 0.3));

	Choice play(sf::Vector2f(WINDOW_WIDTH / 3.5, (WINDOW_HEIGHT / 4.5) + 30),
		sf::Vector2f(1, 1),
		"./Ressources/Img/button.png",
		"./Ressources/Img/button_select.png",
		"./Ressources/Img/button.png",
		"./Ressources/Img/button.png");
	Choice Credit(sf::Vector2f(WINDOW_WIDTH / 3.5, (WINDOW_HEIGHT / 4.5) + 150),
		sf::Vector2f(1, 1),
		"./Ressources/Img/button.png",
		"./Ressources/Img/button_select.png",
		"./Ressources/Img/button.png",
		"./Ressources/Img/button.png");
	Choice rules(sf::Vector2f(WINDOW_WIDTH / 3.5, (WINDOW_HEIGHT / 4.5) + 270),
		sf::Vector2f(1, 1),
		"./Ressources/Img/button.png",
		"./Ressources/Img/button_select.png",
		"./Ressources/Img/button.png",
		"./Ressources/Img/button.png");
	Choice online(sf::Vector2f(WINDOW_WIDTH / 3.5, (WINDOW_HEIGHT / 4.5) + 390),
		sf::Vector2f(1, 1),
		"./Ressources/Img/button.png",
		"./Ressources/Img/button_select.png",
		"./Ressources/Img/button.png",
		"./Ressources/Img/button.png");
	choices.push_back(play);
	choices.push_back(Credit);
	choices.push_back(rules);
	choices.push_back(online);
	*/
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
	int nb_bytes = ceil(nb_revelent / 8.f);			// 90.25 --> 91
	int nb_wasted_bits = 8 - nb_revelent % 8;		// 8 - 2  --> 6
	uint8_t* compressed = new uint8_t[nb_bytes];

	int current = 0;
	short int buff_used = 0;

	const enum Codes : uint8_t	{ empty = 0, black = 1, white = 2, KO = 3 };

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

	int nb_bytes = ceil(nb_revelent / 8.f);			// 90.25 --> 91
	int nb_wasted_bits = 8 - nb_revelent % 8;		// 8 - 2  --> 6

	// Start looking at the first place of the goban so -1 avoid skipping this first location.
	int current = -1;

	uint8_t masque = ~0;
	masque <<= (8 - used_bits);

	const enum Codes : uint8_t { empty = 0, black = 1, white = 2, KO = 3 };

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
