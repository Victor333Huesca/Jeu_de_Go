#include "Globals.h"
#include <thread>
#include "Screens.h"
#include "Menu.h"
#include "Game/Game_window.h"

#define	MULTITHREAD false

void renderingThread(sf::RenderWindow* _window, std::vector<Screen*>* _screens, int* _cur_screen);

Menu* loadMenu1();

int main()
{
	// Main's variables
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH + INFOS_SIZE, WINDOW_HEIGHT), "Jeu de Go");
    std::vector<Screen*> screens;
    int cur_screen = 0;

	// Declare here different screens in order of there use.
	screens.push_back(new Game_window);
	//screens.push_back(loadMenu1());

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
	Menu* menu = new Menu(sf::Vector2f(0.f, 0.f), "./Ressources/Img/Background3.png", sf::Vector2f(0.3f, 0.3f));

	// On charge le style du text
	sf::Text text_style;
	text_style.setCharacterSize(86);
	text_style.setFillColor(sf::Color::Black);
	sf::Font text_font;
	text_font.loadFromFile("./Ressources/Font/time.ttf");
	text_style.setFont(text_font);

	// Position
	sf::Vector2f pos(0, 0);// (WINDOW_WIDTH + INFOS_SIZE - (WINDOW_WIDTH + INFOS_SIZE) / 3.5) / 2, WINDOW_HEIGHT + 100);

	// On charge les items
	menu->addItem(Choice("Jouer", text_style, pos.x, pos.y));
	menu->addItem(Choice("Options", text_style, pos.x, pos.y + 120));
	menu->addItem(Choice("Exemples", text_style, pos.x, pos.y + 240));
	menu->addItem(Choice("Problèmes", text_style, pos.x, pos.y + 360));
	menu->addItem(Choice("Quitter", text_style, pos.x, pos.y + 480));

	// Then set items textures and return the menu
	menu->setItemsTextures("./Ressources/Img/button_blank.png", "./Ressources/Img/button_selected.png");
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
