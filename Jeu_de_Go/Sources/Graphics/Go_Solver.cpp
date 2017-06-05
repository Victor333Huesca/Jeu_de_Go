#include "Go_Solver.h"
#define MUSIC_AT_START false


Go_Solver::Go_Solver() :
	screens(10, nullptr),
	cur_screen(MAIN_MENU),
	musics(5, nullptr),
	cur_music(PISTE_1),
	game(nullptr),
	thread_tsumego(nullptr),
	target_tsumego(Etat()),
	thread_solution()
{
	// Load game first
	game = new Game_window();
	screens[GAME] = game;

	// Load menus -care here, this functions use dynamic allocation-
	loadMenu(MAIN_MENU);
	loadMenu(PROBLEMS_MENU);
	loadMenu(OPTIONS_MENU);
	loadMenu(AUDIO);
	loadMenu(VIDEO);
	loadMenu(PAUSE);

	// Open each music
	musics[PISTE_1] = new sf::Music();
	musics[PISTE_1]->openFromFile("./Ressources/Music/piste_1.ogg");
}


Go_Solver::~Go_Solver()
{
	std::cout << "~Go_Solver()" << std::endl;
	// free the game
	delete game;
	game = nullptr;
	screens[GAME] = nullptr;

	// Free screens
	for (Screen*& sc : screens)
	{
		delete sc;
	}
	screens.clear();

	// Free musics
	for (sf::Music*& msc : musics)
	{
		delete msc;
	}
	musics.clear();

	// clear tsumego
	IA::stop_tsumego();
	if (thread_tsumego)
		thread_tsumego->join();
	delete thread_tsumego;
	thread_tsumego = nullptr;

	// clear solution
	if (thread_solution)
		thread_solution->join();
	delete thread_solution;
	thread_solution = nullptr;
}

void Go_Solver::Run(sf::RenderWindow & window)
{
	// Launch music
	if (MUSIC_AT_START) musics[cur_music]->play();

	//Main loop
	while (cur_screen >= CONTINUE)
	{
		if (screens[cur_screen])
			cur_screen = screens[cur_screen]->Run(window, *this);
		else
			std::cerr << "Le menu demandé n'a pas été chargé !\n";
	}

	musics[cur_music]->stop();
}

/* ----- Charge les différents menus ----- */
// 'Template'
void Go_Solver::loadMenu(const Screens& menu)
{
	// The loaded menu
	Menu* m = nullptr;
	// Look which is demanded
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
		std::cerr << "Le menu demandé (" << menu << ") ne peut être chargé !\n";
		break;
	}

	// Load menu
	screens[menu] = m;
}

// Principal
Menu* Go_Solver::loadMenu1()
{
	// On charge le menu
	Menu_simple* menu = new Menu_simple(sf::Vector2f(0.f, 0.f), "./Ressources/Img/Backgrounds/background3.png", NO_CHANGE, sf::Vector2f(0.3f, 0.3f));

	// Need move aways after
	menu->setItemsFonts("./Ressources/Font/time.ttf");

	// On charge le style du text sauf la police qui est incluse avec le menu.
	sf::Text text_style;
	text_style.setCharacterSize(50);
	text_style.setFillColor(sf::Color::Black);

	// Position
	sf::Vector2f pos(225, 125);

	// On charge les items
	menu->addItem(Choice_Simple(L"        Jouer", text_style, pos.x, pos.y, [](sf::RenderTarget& window, Go_Solver& solver)
	{ return GAME; }));
	menu->addItem(Choice_Simple(L"       Options", text_style, pos.x, pos.y + 120, [](sf::RenderTarget& window, Go_Solver& solver)
	{ return OPTIONS_MENU; }));
	menu->addItem(Choice_Simple(L"   Réinitialiser", text_style, pos.x, pos.y + 240, [](sf::RenderTarget& window, Go_Solver& solver)
	{
		solver.setGoban(Goban());
		return NO_CHANGE;
	}));
	menu->addItem(Choice_Simple(L"      Problèmes", text_style, pos.x, pos.y + 360, [](sf::RenderTarget& window, Go_Solver& solver)
	{ return PROBLEMS_MENU; }));
	menu->addItem(Choice_Simple(L"       Quitter", text_style, pos.x, pos.y + 480, [](sf::RenderTarget& window, Go_Solver& solver)
	{ return EXIT; }));

	// Then set items textures and return the menu
	menu->setItemsTextures("./Ressources/Img/Buttons/button_blank.png", "./Ressources/Img/Buttons/button_selected.png");

	log_file << "\nLe Menu 1 a été chargé\n" << std::endl;

	return menu;
}

// Problèmes
Menu* Go_Solver::loadMenu2()
{
	// On charge le menu
	Menu_Miniature* menu = new Menu_Miniature(sf::Vector2f(0.f, 0.f), "./Ressources/Img/Backgrounds/background1.png", MAIN_MENU, sf::Vector2f(2.f, 2.f));

	// Position
	sf::Vector2f pos(50, 50);


    /* ----------------------- Début page 1 ---------------------- */
	// Retour
	menu->addItem(Choice_miniature("./Ressources/Img/Buttons/retour.png",
		pos.x, pos.y, [](sf::RenderTarget& window, Go_Solver& solver)
	{
		return PREVIOUS;
	}));

	// 6 en coins
	menu->addItem(Choice_miniature("./Ressources/Img/Problems/probleme_6_en_coin_blank.png",
		pos.x + 250, pos.y, [](sf::RenderTarget& window, Go_Solver& solver)
	{
		window.setView(sf::View(sf::FloatRect(0, 0, WINDOW_WIDTH + 200, WINDOW_HEIGHT)));
		solver.setGoban(parseur("./Ressources/Problems/probleme_6_en_coin.go"));
		//game.setView(sf::FloatRect(0, 0, 1200, 1200));
		solver.setTarget(3, 0);
		return GAME;
	}));

	menu->addItem(Choice_miniature("./Ressources/Img/Problems/1_blank.png",
		pos.x + 500, pos.y, [](sf::RenderTarget& window, Go_Solver& solver)
	{
		window.setView(sf::View(sf::FloatRect(0, 0, WINDOW_WIDTH + 200, WINDOW_HEIGHT)));
		solver.setGoban(parseur("./Ressources/Problems/Facile/1.go"));
		//game.setView(sf::FloatRect(0, 0, 1200, 1200));
		return GAME;
	}));

	menu->addItem(Choice_miniature("./Ressources/Img/Problems/2_blank.png",
		pos.x, pos.y + 250, [](sf::RenderTarget& window, Go_Solver& solver)
	{
		window.setView(sf::View(sf::FloatRect(0, 0, WINDOW_WIDTH + 200, WINDOW_HEIGHT)));
		solver.setGoban(parseur("./Ressources/Problems/Facile/2.go"));
		//game.setView(sf::FloatRect(0, 0, 1200, 1200));
		return GAME;
	}));

	menu->addItem(Choice_miniature("./Ressources/Img/Problems/3_blank.png",
		pos.x + 250, pos.y + 250, [](sf::RenderTarget& window, Go_Solver& solver)
	{
		window.setView(sf::View(sf::FloatRect(0, 0, WINDOW_WIDTH + 200, WINDOW_HEIGHT)));
		solver.setGoban(parseur("./Ressources/Problems/Facile/3.go"));
		//game.setView(sf::FloatRect(0, 0, 1200, 1200));
		return GAME;
	}));

	menu->addItem(Choice_miniature("./Ressources/Img/Problems/4_blank.png",
		pos.x + 500, pos.y + 250, [](sf::RenderTarget& window, Go_Solver& solver)
	{
		window.setView(sf::View(sf::FloatRect(0, 0, WINDOW_WIDTH + 200, WINDOW_HEIGHT)));
		solver.setGoban(parseur("./Ressources/Problems/Facile/4.go"));
		//game.setView(sf::FloatRect(0, 0, 1000, 1000));
		return GAME;
	}));

	menu->addItem(Choice_miniature("./Ressources/Img/Problems/5_blank.png",
		pos.x, pos.y + 500, [](sf::RenderTarget& window, Go_Solver& solver)
	{
		window.setView(sf::View(sf::FloatRect(0, 0, WINDOW_WIDTH + 200, WINDOW_HEIGHT)));
		solver.setGoban(parseur("./Ressources/Problems/Facile/5.go"));
		//game.setView(sf::FloatRect(0, 0, 1200, 1200));
		return GAME;
	}));

	menu->addItem(Choice_miniature("./Ressources/Img/Problems/6_blank.png",
		pos.x + 250, pos.y + 500, [](sf::RenderTarget& window, Go_Solver& solver)
	{
		window.setView(sf::View(sf::FloatRect(0, 0, WINDOW_WIDTH + 200, WINDOW_HEIGHT)));
		solver.setGoban(parseur("./Ressources/Problems/Facile/6.go"));
		//game.setView(sf::FloatRect(0, 0, 1200, 1200));
		return GAME;
	}));

	menu->addItem(Choice_miniature("./Ressources/Img/Buttons/suivant.png",
		pos.x + 500, pos.y + 500, [](sf::RenderTarget& window, Go_Solver& solver)
	{
		window.setView(sf::View(sf::FloatRect(1000, 0, WINDOW_WIDTH + 200, WINDOW_HEIGHT)));
		return NO_CHANGE;
	}));
    /* -----------------------  Fin page 1  ---------------------- */


    /* ----------------------- Début page 2 ---------------------- */
    pos.x += 1000;

	// Retour
	menu->addItem(Choice_miniature("./Ressources/Img/Buttons/retour.png",
		pos.x, pos.y, [](sf::RenderTarget& window, Go_Solver& solver)
	{
		window.setView(sf::View(sf::FloatRect(0, 0, WINDOW_WIDTH + 200, WINDOW_HEIGHT)));
		return NO_CHANGE;
	}));

	menu->addItem(Choice_miniature("./Ressources/Img/Problems/7_blank.png",
		pos.x + 250, pos.y, [](sf::RenderTarget& window, Go_Solver& solver)
	{
		window.setView(sf::View(sf::FloatRect(0, 0, WINDOW_WIDTH + 200, WINDOW_HEIGHT)));
		solver.setGoban(parseur("./Ressources/Problems/Facile/7.go"));
		//game.setView(sf::FloatRect(0, 0, 1200, 1200));
		return GAME;
	}));

	menu->addItem(Choice_miniature("./Ressources/Img/Problems/8_blank.png",
		pos.x + 500, pos.y, [](sf::RenderTarget& window, Go_Solver& solver)
	{
		window.setView(sf::View(sf::FloatRect(0, 0, WINDOW_WIDTH + 200, WINDOW_HEIGHT)));
		solver.setGoban(parseur("./Ressources/Problems/Facile/8.go"));
		//game.setView(sf::FloatRect(0, 0, 1200, 1200));
		return GAME;
	}));

	menu->addItem(Choice_miniature("./Ressources/Img/Problems/9_blank.png",
		pos.x, pos.y + 250, [](sf::RenderTarget& window, Go_Solver& solver)
	{
		window.setView(sf::View(sf::FloatRect(0, 0, WINDOW_WIDTH + 200, WINDOW_HEIGHT)));
		solver.setGoban(parseur("./Ressources/Problems/Facile/9.go"));
		//game.setView(sf::FloatRect(0, 0, 1200, 1200));
		return GAME;
	}));

	menu->addItem(Choice_miniature("./Ressources/Img/Problems/10_blank.png",
		pos.x + 250, pos.y + 250, [](sf::RenderTarget& window, Go_Solver& solver)
	{
		window.setView(sf::View(sf::FloatRect(0, 0, WINDOW_WIDTH + 200, WINDOW_HEIGHT)));
		solver.setGoban(parseur("./Ressources/Problems/Facile/10.go"));
		//game.setView(sf::FloatRect(0, 0, 1200, 1200));
		return GAME;
	}));

	menu->addItem(Choice_miniature("./Ressources/Img/Problems/11_blank.png",
		pos.x + 500, pos.y + 250, [](sf::RenderTarget& window, Go_Solver& solver)
	{
		window.setView(sf::View(sf::FloatRect(0, 0, WINDOW_WIDTH + 200, WINDOW_HEIGHT)));
		solver.setGoban(parseur("./Ressources/Problems/Facile/11.go"));
		//game.setView(sf::FloatRect(0, 0, 1200, 1200));
		return GAME;
	}));

	menu->addItem(Choice_miniature("./Ressources/Img/Problems/12_blank.png",
		pos.x, pos.y + 500, [](sf::RenderTarget& window, Go_Solver& solver)
	{
		window.setView(sf::View(sf::FloatRect(0, 0, WINDOW_WIDTH + 200, WINDOW_HEIGHT)));
		solver.setGoban(parseur("./Ressources/Problems/Facile/12.go"));
		//game.setView(sf::FloatRect(0, 0, 1200, 1200));
		return GAME;
	}));

	menu->addItem(Choice_miniature("./Ressources/Img/Problems/13_blank.png",
		pos.x + 250, pos.y + 500, [](sf::RenderTarget& window, Go_Solver& solver)
	{
		window.setView(sf::View(sf::FloatRect(0, 0, WINDOW_WIDTH + 200, WINDOW_HEIGHT)));
		solver.setGoban(parseur("./Ressources/Problems/Facile/13.go"));
		//game.setView(sf::FloatRect(0, 0, 1200, 1200));
		return GAME;
	}));

	menu->addItem(Choice_miniature("./Ressources/Img/Buttons/suivant.png",
		pos.x + 500, pos.y + 500, [](sf::RenderTarget& window, Go_Solver& solver)
	{
		window.setView(sf::View(sf::FloatRect(2000, 0, WINDOW_WIDTH + 200, WINDOW_HEIGHT)));
		return NO_CHANGE;
	}));
	/* -----------------------  Fin page 2  ---------------------- */


    /* ----------------------- Début page 3 ---------------------- */
    pos.x += 1000;

	// Retour
	menu->addItem(Choice_miniature("./Ressources/Img/Buttons/retour.png",
		pos.x, pos.y, [](sf::RenderTarget& window, Go_Solver& solver)
	{
		window.setView(sf::View(sf::FloatRect(1000, 0, WINDOW_WIDTH + 200, WINDOW_HEIGHT)));
		return NO_CHANGE;
	}));

	menu->addItem(Choice_miniature("./Ressources/Img/Problems/14_blank.png",
		pos.x + 250, pos.y, [](sf::RenderTarget& window, Go_Solver& solver)
	{
		window.setView(sf::View(sf::FloatRect(0, 0, WINDOW_WIDTH + 200, WINDOW_HEIGHT)));
		solver.setGoban(parseur("./Ressources/Problems/14.go"));
		//game.setView(sf::FloatRect(0, 0, 1200, 1200));
		return GAME;
	}));

	menu->addItem(Choice_miniature("./Ressources/Img/Problems/15_blank.png",
		pos.x + 500, pos.y, [](sf::RenderTarget& window, Go_Solver& solver)
	{
		window.setView(sf::View(sf::FloatRect(0, 0, WINDOW_WIDTH + 200, WINDOW_HEIGHT)));
		solver.setGoban(parseur("./Ressources/Problems/Facile/15.go"));
		//game.setView(sf::FloatRect(0, 0, 1200, 1200));
		return GAME;
	}));

	menu->addItem(Choice_miniature("./Ressources/Img/Problems/16_blank.png",
		pos.x, pos.y + 250, [](sf::RenderTarget& window, Go_Solver& solver)
	{
		window.setView(sf::View(sf::FloatRect(0, 0, WINDOW_WIDTH + 200, WINDOW_HEIGHT)));
		solver.setGoban(parseur("./Ressources/Problems/Facile/16.go"));
		//game.setView(sf::FloatRect(0, 0, 1200, 1200));
		return GAME;
	}));

	menu->addItem(Choice_miniature("./Ressources/Img/Problems/17_blank.png",
		pos.x + 250, pos.y + 250, [](sf::RenderTarget& window, Go_Solver& solver)
	{
		window.setView(sf::View(sf::FloatRect(0, 0, WINDOW_WIDTH + 200, WINDOW_HEIGHT)));
		solver.setGoban(parseur("./Ressources/Problems/Facile/17.go"));
		//game.setView(sf::FloatRect(0, 0, 1200, 1200));
		return GAME;
	}));

	menu->addItem(Choice_miniature("./Ressources/Img/Problems/18_blank.png",
		pos.x + 500, pos.y + 250, [](sf::RenderTarget& window, Go_Solver& solver)
	{
		window.setView(sf::View(sf::FloatRect(0, 0, WINDOW_WIDTH + 200, WINDOW_HEIGHT)));
		solver.setGoban(parseur("./Ressources/Problems/Facile/18.go"));
		//game.setView(sf::FloatRect(0, 0, 1200, 1200));
		return GAME;
	}));

	menu->addItem(Choice_miniature("./Ressources/Img/Problems/19_blank.png",
		pos.x, pos.y + 500, [](sf::RenderTarget& window, Go_Solver& solver)
	{
		window.setView(sf::View(sf::FloatRect(0, 0, WINDOW_WIDTH + 200, WINDOW_HEIGHT)));
		solver.setGoban(parseur("./Ressources/Problems/Facile/19.go"));
		//game.setView(sf::FloatRect(0, 0, 1200, 1200));
		return GAME;
	}));

	menu->addItem(Choice_miniature("./Ressources/Img/Problems/20_blank.png",
		pos.x + 250, pos.y + 500, [](sf::RenderTarget& window, Go_Solver& solver)
	{
		window.setView(sf::View(sf::FloatRect(0, 0, WINDOW_WIDTH + 200, WINDOW_HEIGHT)));
		solver.setGoban(parseur("./Ressources/Problems/Facile/20.go"));
		//game.setView(sf::FloatRect(0, 0, 1200, 1200));
		return GAME;
	}));

	menu->addItem(Choice_miniature("./Ressources/Img/Buttons/suivant.png",
		pos.x + 500, pos.y + 500, [](sf::RenderTarget& window, Go_Solver& solver)
	{
		window.setView(sf::View(sf::FloatRect(3000, 0, WINDOW_WIDTH + 200, WINDOW_HEIGHT)));
		return NO_CHANGE;
	}));
    /* -----------------------  Fin page 3  ---------------------- */


    /* ----------------------- Début page 4 ---------------------- */
    pos.x += 1000;

	// Retour
	menu->addItem(Choice_miniature("./Ressources/Img/Buttons/retour.png",
		pos.x, pos.y, [](sf::RenderTarget& window, Go_Solver& solver)
	{
		window.setView(sf::View(sf::FloatRect(2000, 0, WINDOW_WIDTH + 200, WINDOW_HEIGHT)));
		return NO_CHANGE;
	}));

	menu->addItem(Choice_miniature("./Ressources/Img/Problems/21_blank.png",
		pos.x + 250, pos.y, [](sf::RenderTarget& window, Go_Solver& solver)
	{
		window.setView(sf::View(sf::FloatRect(0, 0, WINDOW_WIDTH + 200, WINDOW_HEIGHT)));
		solver.setGoban(parseur("./Ressources/Problems/21.go"));
		//game.setView(sf::FloatRect(0, 0, 1200, 1200));
		return GAME;
	}));

	menu->addItem(Choice_miniature("./Ressources/Img/Problems/22_blank.png",
		pos.x + 500, pos.y, [](sf::RenderTarget& window, Go_Solver& solver)
	{
		window.setView(sf::View(sf::FloatRect(0, 0, WINDOW_WIDTH + 200, WINDOW_HEIGHT)));
		solver.setGoban(parseur("./Ressources/Problems/Facile/22.go"));
		//game.setView(sf::FloatRect(0, 0, 1200, 1200));
		return GAME;
	}));

	menu->addItem(Choice_miniature("./Ressources/Img/Problems/presentation.png",
		pos.x, pos.y + 250, [](sf::RenderTarget& window, Go_Solver& solver)
	{
		window.setView(sf::View(sf::FloatRect(0, 0, WINDOW_WIDTH + 200, WINDOW_HEIGHT)));
		solver.setGoban(parseur("./Ressources/Problems/presentation.go"));

		//game.setView(sf::FloatRect(0, 0, 1200, 1200));
		return GAME;
	}));

	menu->addItem(Choice_miniature("./Ressources/Img/Problems/void.png",
		pos.x + 250, pos.y + 250, [](sf::RenderTarget& window, Go_Solver& solver)
	{
		window.setView(sf::View(sf::FloatRect(0, 0, WINDOW_WIDTH + 200, WINDOW_HEIGHT)));
		solver.setGoban(parseur("./Ressources/Problems/void.go"));

		//game.setView(sf::FloatRect(0, 0, 1200, 1200));
		return GAME;
	}));

	/*menu->addItem(Choice_miniature("./Ressources/Img/Buttons/suivant.png",
	pos.x + 500, pos.y + 500, [](sf::RenderTarget& window, Go_Solver& solver)
	{
	window.setView(sf::View(sf::FloatRect(4000, 0, WINDOW_WIDTH + 200, WINDOW_HEIGHT)));
	return NO_CHANGE;
	}));*/



    /* -----------------------  Fin page 4  ---------------------- */


	// On applique les textures
	menu->setItemsTextures("./Ressources/Img/Buttons/miniature_selected.png", "./Ressources/Img/Buttons/miniature_selected.png");

	log_file << "\nLe Menu probleme a été chargé\n" << std::endl;

	return menu;
}

// Options
Menu* Go_Solver::loadMenu3()
{
	// On charge le menu
	Menu_simple* menu = new Menu_simple(sf::Vector2f(0.f, 0.f), "./Ressources/Img/Backgrounds/background3.png", MAIN_MENU, sf::Vector2f(0.3f, 0.3f));

	// Need move aways after
	menu->setItemsFonts("./Ressources/Font/time.ttf");

	// On charge le style du text sauf la police qui est incluse avec le menu.
	sf::Text text_style;
	text_style.setCharacterSize(50);
	text_style.setFillColor(sf::Color::Black);

	// Position
	sf::Vector2f pos(225, 200);

	// On charge les items
	menu->addItem(Choice_Simple(L"        Audio", text_style, pos.x, pos.y, [](sf::RenderTarget& window, Go_Solver& solver)
	{ return AUDIO; }));
	menu->addItem(Choice_Simple(L"        Vidéo", text_style, pos.x, pos.y + 120, [](sf::RenderTarget& window, Go_Solver& solver)
	{ return VIDEO; }));
	menu->addItem(Choice_Simple(L"        Retour", text_style, pos.x, pos.y + 240, [](sf::RenderTarget& window, Go_Solver& solver)
	{ return PREVIOUS; }));

	// Then set items textures and return the menu
	menu->setItemsTextures("./Ressources/Img/Buttons/button_blank.png", "./Ressources/Img/Buttons/button_selected.png");

	log_file << "\nLe Menu 3 à été chargé\n" << std::endl;

	return menu;
}

// Audio
Menu* Go_Solver::loadMenu4()
{
	// On charge le menu
	Menu_simple* menu = new Menu_simple(sf::Vector2f(0.f, 0.f), "./Ressources/Img/Backgrounds/background3.png", OPTIONS_MENU, sf::Vector2f(0.3f, 0.3f));

	// Need move aways after
	menu->setItemsFonts("./Ressources/Font/time.ttf");

	// On charge le style du text sauf la police qui est incluse avec le menu.
	sf::Text text_style;
	text_style.setCharacterSize(50);
	text_style.setFillColor(sf::Color::Black);

	// Position
	sf::Vector2f pos(225, 200);

	// On charge les items

	/* Pour les volumes dans un premier temps afficher juste un sprite avec : Aucun, Léger, Moyen, Fort, Trés Fort
	Créer directement une barre de progression risque d'être bien trop long et fastidieux*/

	menu->addItem(Choice_Simple(L"      Musiques", text_style, pos.x, pos.y, [](sf::RenderTarget& window, Go_Solver& solver)
	{
		solver.turnMusicUp();
		return NO_CHANGE;
	}));
	menu->addItem(Choice_Simple(L"         Sons", text_style, pos.x, pos.y + 120, [](sf::RenderTarget& window, Go_Solver& solver)
	{
		solver.turnSoundsUp();
		return NO_CHANGE;
	}));
	menu->addItem(Choice_Simple(L"        Retour", text_style, pos.x, pos.y + 240, [](sf::RenderTarget& window, Go_Solver& solver)
	{ return PREVIOUS; }));

	// Then set items textures and return the menu
	menu->setItemsTextures("./Ressources/Img/Buttons/button_blank.png", "./Ressources/Img/Buttons/button_selected.png");

	log_file << "\nLe Menu 4 à été chargé\n" << std::endl;

	return menu;
}

// Vidéo
Menu* Go_Solver::loadMenu5()
{
	// On charge le menu
	Menu_simple* menu = new Menu_simple(sf::Vector2f(0.f, 0.f), "./Ressources/Img/Backgrounds/background3.png", OPTIONS_MENU, sf::Vector2f(0.3f, 0.3f));

	// Need move aways after
	menu->setItemsFonts("./Ressources/Font/time.ttf");

	// On charge le style du text sauf la police qui est incluse avec le menu.
	sf::Text text_style;
	text_style.setCharacterSize(50);
	text_style.setFillColor(sf::Color::Black);

	// Position
	sf::Vector2f pos(225, 200);

	// On charge les items
	menu->addItem(Choice_Simple(L"        Retour", text_style, pos.x, pos.y + 240, [](sf::RenderTarget& window, Go_Solver& solver)
	{ return PREVIOUS; }));

	// Then set items textures and return the menu
	menu->setItemsTextures("./Ressources/Img/Buttons/button_blank.png", "./Ressources/Img/Buttons/button_selected.png");

	log_file << "\nLe Menu 5 à été chargé\n" << std::endl;

	return menu;
}

// Menu pause
Menu* Go_Solver::loadMenu6()
{
	// On charge le menu
	Menu_simple* menu = new Menu_simple(sf::Vector2f(0.f, 0.f), "./Ressources/Img/Backgrounds/background3.png", GAME, sf::Vector2f(0.3f, 0.3f));

	// Need move aways after
	menu->setItemsFonts("./Ressources/Font/time.ttf");

	// On charge le style du text sauf la police qui est incluse avec le menu.
	sf::Text text_style;
	text_style.setCharacterSize(44);
	text_style.setFillColor(sf::Color::Black);

	// Position
	sf::Vector2f pos(225, 80);

	// On charge les items
	menu->addItem(Choice_Simple(L"       Options", text_style, pos.x, pos.y, [](sf::RenderTarget& window, Go_Solver& solver)
	{ return OPTIONS_MENU; }));
	menu->addItem(Choice_Simple(L"    Retour au jeu", text_style, pos.x, pos.y + 120, [](sf::RenderTarget& window, Go_Solver& solver)
	{ return PREVIOUS; }));
	menu->addItem(Choice_Simple(L"Lancer le Tsumego", text_style, pos.x, pos.y + 240, [](sf::RenderTarget& window, Go_Solver& solver)
	{
		solver.launchTsumego();
		return GAME;
	}));
	menu->addItem(Choice_Simple(L" Stoper Tsumego", text_style, pos.x, pos.y + 360, [](sf::RenderTarget& window, Go_Solver& solver)
	{
		IA::stop_tsumego();
		return GAME;
	}));
	menu->addItem(Choice_Simple(L" Quitter la partie", text_style, pos.x, pos.y + 480, [](sf::RenderTarget& window, Go_Solver& solver)
	{ return MAIN_MENU; }));
	menu->addItem(Choice_Simple(L"Revenir au bureau", text_style, pos.x, pos.y + 600, [](sf::RenderTarget& window, Go_Solver& solver)
	{ return EXIT; }));

	// Then set items textures and return the menu
	menu->setItemsTextures("./Ressources/Img/Buttons/button_blank.png", "./Ressources/Img/Buttons/button_selected.png");

	log_file << "\nLe Menu 3 à été chargé\n" << std::endl;

	return menu;
}
/* ----- Fin du cargement des menus ----- */

const sf::Music& Go_Solver::getMusic() const
{
	return *musics[cur_music];
}

void Go_Solver::setMusic(const Musics & mus)
{
	musics[cur_music]->stop();
	cur_music = mus;
	musics[cur_music]->play();
}

void Go_Solver::turnMusicUp()
{
	float vol = getMusic().getVolume();
	vol += 33.f;
	if (vol > 100.f)	vol = 0.f;
	musics[cur_music]->setVolume(vol);
}

void Go_Solver::turnMusicDown()
{
	float vol = getMusic().getVolume();
	vol -= 33.f;
	if (vol < 0.f)	vol = 100.f;
	musics[cur_music]->setVolume(vol);
}

void Go_Solver::turnSoundsUp()
{
	game->turnSoundsUp();
}

void Go_Solver::turnSoundsDown()
{
	game->turnSoundsDown();
}

void Go_Solver::setGoban(const Goban & goban)
{
	game->setGoban(goban);
}

Goban Go_Solver::getGoban() const
{
	return game->getGoban();
}

void Go_Solver::setTarget(const Etat & state)
{
	target_tsumego = state;
}

void Go_Solver::setTarget(int x, int y)
{
	target_tsumego = game->getGoban().coord(x, y);
}

void Go_Solver::launchTsumego()
{
	/* On abandonne cette idée le Tsumego n'a vraiment
	pas été penssé pour être utilisable proprement...

	std::cout << "lancement du tsumego :" << std::endl;
	sf::Text txt;
	sf::Font font;
	font.loadFromFile("./Ressources/Font/time.ttf");
	txt.setFont(font);
	txt.setCharacterSize(50);
	txt.setFillColor(sf::Color::Blue);
	txt.setPosition(sf::Vector2f(100, 300));
	window.draw(txt); */

	Arbre abr(getGoban(), Etat::BLANC);
    /*
	// Launch tsumego (stop previous one before if needed)

#if defined(_WIN32) || MULTITHREAD
	IA::stop_tsumego();
	if (thread_tsumego)
		thread_tsumego->join();
	delete thread_tsumego;
	thread_tsumego = nullptr;
	try
	{
		//thread_tsumego = new std::thread(IA::Tsumego, &abr, &target_tsumego);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
		throw;
	}
#else
	//IA::Tsumego(&abr, &target_tsumego);
#endif
    */

    // Start Tsumego
	int x, y;
	std::cout << "Veuillez saisir les coordonnées de la cible :" << std::endl;
	std::cin >> x >> y;
	setTarget(x, y);

	std::list<Goban> sol = IA::Tsumego(&abr, &target_tsumego);

	/* ----- Je précise que j'ai bien include <thread> ----- */
	if (thread_solution)
	{
		thread_solution->join();
		delete thread_solution;
		thread_solution = nullptr;
	}

	thread_solution = new std::thread(&Go_Solver::solution, this, &sol);
}

const std::vector<Screen*>& Go_Solver::getScreens() const
{
	return screens;
}

const Screens& Go_Solver::getScreen() const
{
	return cur_screen;
}

void Go_Solver::solution(const std::list<Goban>* sol)
{
	std::list<Goban>::const_iterator it = sol->begin();
	//std::_List_const_iterator<Goban> it2 = 

	while (true)
	{
		setGoban(*it);
		it++;
		if (it == sol->end())
			it = sol->begin();
		std::this_thread::sleep_for(std::chrono::seconds(2));
	}
}