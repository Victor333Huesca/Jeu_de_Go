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

#define	MULTITHREAD false

void renderingThread(sf::RenderWindow* _window, std::vector<Screen*>* _screens, Screens* _cur_screen);

// Diff�rents menus
void loadMenu(std::vector<Screen*>& screens, const Screens& menu);
Menu* loadMenu1();
Menu* loadMenu2();
Menu* loadMenu3();
Menu* loadMenu4();
Menu* loadMenu5();
Menu* loadMenu6();

// A d�placer en m�thode de Goban (sauf le test �videment)
uint8_t* compressGoban(const Goban& goban, int nb_revelent = 0);
void uncompressGoban(const uint8_t* compressed, const Etat::VAL KO_status, Goban& goban, int nb_revelent = 0);
void test();

extern std::ofstream log_file("trace.log");

int main()
{
	// Main's variables
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH + INFOS_SIZE, WINDOW_HEIGHT), "Jeu de Go");
    std::vector<Screen*> screens(10, nullptr);
    Screens cur_screen = MAIN_MENU;

	// Music !
	std::vector<sf::Music> musics(5);
	sf::Music* cur_music = &musics[PISTE_1];

	// Open each music
	musics[PISTE_1].openFromFile("./Ressources/Music/piste_1.ogg");


	// The game
	Game_window* game = new Game_window();

	// Declare here different screens
	screens[GAME] = game;
	loadMenu(screens, MAIN_MENU);
	loadMenu(screens, PROBLEMS_MENU);
	loadMenu(screens, OPTIONS_MENU);
	loadMenu(screens, AUDIO);
	loadMenu(screens, VIDEO);
	loadMenu(screens, PAUSE);

#if defined(_WIN32) || MULTITHREAD
	// disable window's context
	window.setActive(false);

	// Launch thread
	std::thread thread_rendering(renderingThread, &window, &screens, &cur_screen);
#endif

	window.setFramerateLimit(60);
	cur_music->play();

	//Main loop
	while (cur_screen >= CONTINUE)
	{
		if (screens[cur_screen])
			cur_screen = screens[cur_screen]->Run(window, *game);
		else
			std::cerr << "Le menu demand� n'a pas �t� charg� !\n";
	}

	// Wait for the rendering thread has finished its instructions before exit
#if defined(_WIN32) || MULTITHREAD
	thread_rendering.join();
#endif

	// Close window & cie
	window.close();
	log_file.close();
	cur_music->stop();

	// Free screens
	for (Screen*& sc : screens)
	{
		delete sc;
	}
	screens.clear();

#ifdef _WIN32
	system("start notepad trace.log");
	system("pause");
#else
	system("gedit trace.log&");
#endif // _WIN32

	return 0;
}

// Render
void renderingThread(sf::RenderWindow* _window, std::vector<Screen*>* _screens, Screens* _cur_screen)
{
	// Get the render window
	sf::RenderWindow& window = *_window;
	std::vector<Screen*>& screens = *_screens;
	Screens& cur_screen = *_cur_screen;

	while (cur_screen >= CONTINUE)
	{
		// Clear the window with a black screen
		window.clear(sf::Color::Black);

		// Draw everything here
		window.draw(*screens[cur_screen]);

		// End of current frame, display everything
		window.display();
	}
}

// 'Template'
void loadMenu(std::vector<Screen*>& screens, const Screens& menu)
{
	// The loaded menu
	Menu* m = nullptr;

	// Look witch is demanded
	switch (menu)
	{
	case MAIN_MENU:
		m = loadMenu1();
		break;
	case PROBLEMS_MENU:
		m = loadMenu2();
		break;
	case OPTIONS_MENU:
		m = loadMenu3();
		break;
	case AUDIO:
		m = loadMenu4();
		break;
	case VIDEO:
		m = loadMenu5();
		break;
	case PAUSE:
		m = loadMenu6();
		break;
	default:
		std::cerr << "Le menu demand� (" << menu << ") ne peut �tre charg� !\n";
		break;
	}

	// Load menu
	screens[menu] = m;
}

// Principal
Menu* loadMenu1()
{
	// On charge le menu
	Menu_simple* menu = new Menu_simple(sf::Vector2f(0.f, 0.f), "./Ressources/Img/Background3.png", NO_CHANGE, sf::Vector2f(0.3f, 0.3f));

	// Need move aways after
	menu->setItemsFonts("./Ressources/Font/time.ttf");

	// On charge le style du text sauf la police qui est incluse avec le menu.
	sf::Text text_style;
	text_style.setCharacterSize(50);
	text_style.setFillColor(sf::Color::Black);

	// Position
	sf::Vector2f pos(225, 125);// (WINDOW_WIDTH + INFOS_SIZE - (WINDOW_WIDTH + INFOS_SIZE) / 3.5) / 2, WINDOW_HEIGHT + 100);

	// On charge les items
	menu->addItem(Choice_Simple("        Jouer", text_style, pos.x, pos.y,	[](const sf::RenderTarget& window, Game_window& game)
	{ return GAME; }));
	menu->addItem(Choice_Simple("       Options", text_style, pos.x, pos.y + 120, [](const sf::RenderTarget& window, Game_window& game)
	{ return OPTIONS_MENU; }));
	menu->addItem(Choice_Simple("      Exemples", text_style, pos.x, pos.y + 240, [](const sf::RenderTarget& window, Game_window& game)
	{ return NO_CHANGE; }));
	menu->addItem(Choice_Simple("      Probl�mes", text_style, pos.x, pos.y + 360, [](const sf::RenderTarget& window, Game_window& game)
	{ return PROBLEMS_MENU; }));
	menu->addItem(Choice_Simple("       Quitter", text_style, pos.x, pos.y + 480, [](const sf::RenderTarget& window, Game_window& game)
	{ return EXIT; }));

	// Then set items textures and return the menu
	menu->setItemsTextures("./Ressources/Img/button_blank.png", "./Ressources/Img/button_selected.png");

	log_file << "\nLe Menu 1 � �t� charg�\n" << std::endl;

	return menu;
}

// Probl�mes
Menu* loadMenu2()
{
	// On charge le menu
	Menu_Miniature* menu = new Menu_Miniature(sf::Vector2f(0.f, 0.f), "./Ressources/Img/Background2.png", MAIN_MENU, sf::Vector2f(0.3f, 0.3f));

	// Position
	sf::Vector2f pos(50, 50);

	/* -----  On charge les items  ----- */
	// Retour
	menu->addItem(Choice_miniature("./Ressources/Img/retour.png",
		pos.x, pos.y, [](const sf::RenderTarget& window, Game_window& game)
	{
		return PREVIOUS;
	}));

	// 6 en coins
	menu->addItem(Choice_miniature("./Ressources/Img/probleme_6_en_coin_blank.png",
		pos.x + 250, pos.y, [](const sf::RenderTarget& window, Game_window& game)
	{
		game.setGoban(parseur("./Ressources/Problems/probleme_6_en_coin.go"));
		game.setView(sf::FloatRect(0, 0, 1200, 1200));
		return GAME;
	}));

	/* --- Fin du chargement des items  --- */


	// On applique les textures
	menu->setItemsTextures("./Ressources/Img/miniature_selected.png", "./Ressources/Img/miniature_selected.png");

	log_file << "\nLe Menu 2 � �t� charg�\n" << std::endl;

	return menu;
}

// Options
Menu* loadMenu3()
{
	// On charge le menu
	Menu_simple* menu = new Menu_simple(sf::Vector2f(0.f, 0.f), "./Ressources/Img/Background3.png", MAIN_MENU, sf::Vector2f(0.3f, 0.3f));

	// Need move aways after
	menu->setItemsFonts("./Ressources/Font/time.ttf");

	// On charge le style du text sauf la police qui est incluse avec le menu.
	sf::Text text_style;
	text_style.setCharacterSize(50);
	text_style.setFillColor(sf::Color::Black);

	// Position
	sf::Vector2f pos(225, 200);

	// On charge les items
	menu->addItem(Choice_Simple("        Audio", text_style, pos.x, pos.y, [](const sf::RenderTarget& window, Game_window& game)
	{ return AUDIO; }));
	menu->addItem(Choice_Simple("        Vid�o", text_style, pos.x, pos.y + 120, [](const sf::RenderTarget& window, Game_window& game)
	{ return VIDEO; }));
	menu->addItem(Choice_Simple("        Retour", text_style, pos.x, pos.y + 240, [](const sf::RenderTarget& window, Game_window& game)
	{ return PREVIOUS; }));

	// Then set items textures and return the menu
	menu->setItemsTextures("./Ressources/Img/button_blank.png", "./Ressources/Img/button_selected.png");

	log_file << "\nLe Menu 3 � �t� charg�\n" << std::endl;

	return menu;
}

// Audio
Menu* loadMenu4()
{
	// On charge le menu
	Menu_simple* menu = new Menu_simple(sf::Vector2f(0.f, 0.f), "./Ressources/Img/Background3.png", OPTIONS_MENU, sf::Vector2f(0.3f, 0.3f));

	// Need move aways after
	menu->setItemsFonts("./Ressources/Font/time.ttf");

	// On charge le style du text sauf la police qui est incluse avec le menu.
	sf::Text text_style;
	text_style.setCharacterSize(50);
	text_style.setFillColor(sf::Color::Black);

	// Position
	sf::Vector2f pos(225, 200);

	// On charge les items

	/* Pour les volumes dans un premier temps afficher juste un sprite avec : Aucun, L�ger, Moyen, Fort, Tr�s Fort
	Cr�er directement une barre de progression risque d'�tre bien trop long et fastidieux*/

	menu->addItem(Choice_Simple("      Musiques", text_style, pos.x, pos.y, [](const sf::RenderTarget& window, Game_window& game)
	{ return NO_CHANGE; }));
	menu->addItem(Choice_Simple("         Sons", text_style, pos.x, pos.y + 120, [](const sf::RenderTarget& window, Game_window& game)
	{ return NO_CHANGE; }));
	menu->addItem(Choice_Simple("        Retour", text_style, pos.x, pos.y + 240, [](const sf::RenderTarget& window, Game_window& game)
	{ return PREVIOUS; }));

	// Then set items textures and return the menu
	menu->setItemsTextures("./Ressources/Img/button_blank.png", "./Ressources/Img/button_selected.png");

	log_file << "\nLe Menu 4 � �t� charg�\n" << std::endl;

	return menu;
}

// Vid�o
Menu* loadMenu5()
{
	// On charge le menu
	Menu_simple* menu = new Menu_simple(sf::Vector2f(0.f, 0.f), "./Ressources/Img/Background3.png", OPTIONS_MENU, sf::Vector2f(0.3f, 0.3f));

	// Need move aways after
	menu->setItemsFonts("./Ressources/Font/time.ttf");

	// On charge le style du text sauf la police qui est incluse avec le menu.
	sf::Text text_style;
	text_style.setCharacterSize(50);
	text_style.setFillColor(sf::Color::Black);

	// Position
	sf::Vector2f pos(225, 200);

	// On charge les items
	menu->addItem(Choice_Simple("        Retour", text_style, pos.x, pos.y + 240, [](const sf::RenderTarget& window, Game_window& game)
	{ return PREVIOUS; }));

	// Then set items textures and return the menu
	menu->setItemsTextures("./Ressources/Img/button_blank.png", "./Ressources/Img/button_selected.png");

	log_file << "\nLe Menu 5 � �t� charg�\n" << std::endl;

	return menu;
}

// Menu pause
Menu* loadMenu6()
{
	// On charge le menu
	Menu_simple* menu = new Menu_simple(sf::Vector2f(0.f, 0.f), "./Ressources/Img/Background3.png", GAME, sf::Vector2f(0.3f, 0.3f));

	// Need move aways after
	menu->setItemsFonts("./Ressources/Font/time.ttf");

	// On charge le style du text sauf la police qui est incluse avec le menu.
	sf::Text text_style;
	text_style.setCharacterSize(44);
	text_style.setFillColor(sf::Color::Black);

	// Position
	sf::Vector2f pos(225, 125);

	// On charge les items
	menu->addItem(Choice_Simple("       Options", text_style, pos.x, pos.y, [](const sf::RenderTarget& window, Game_window& game)
	{ return OPTIONS_MENU; }));
	menu->addItem(Choice_Simple("    Retour au jeu", text_style, pos.x, pos.y + 120, [](const sf::RenderTarget& window, Game_window& game)
	{ return PREVIOUS; }));
	menu->addItem(Choice_Simple(" Quitter la partie", text_style, pos.x, pos.y + 240, [](const sf::RenderTarget& window, Game_window& game)
	{ return MAIN_MENU; }));
	menu->addItem(Choice_Simple("Revenir au bureau", text_style, pos.x, pos.y + 360, [](const sf::RenderTarget& window, Game_window& game)
	{ return EXIT; }));

	// Then set items textures and return the menu
	menu->setItemsTextures("./Ressources/Img/button_blank.png", "./Ressources/Img/button_selected.png");

	log_file << "\nLe Menu 3 � �t� charg�\n" << std::endl;

	return menu;
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

	int nb_bytes = (int)ceil(nb_revelent / 8.f);			// 90.25 --> 91
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
