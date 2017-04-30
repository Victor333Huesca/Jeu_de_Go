#pragma once
#include "Globals.h"
#include "Screens.h"
#include "../Engine/Parser.h"

class Go_Solver
{
public:
	Go_Solver();
	~Go_Solver();

	void Run(sf::RenderWindow& window);

	// Menus loading
	void loadMenu(const Screens& menu);
	static Menu* loadMenu1();
	static Menu* loadMenu2();
	static Menu* loadMenu3();
	static Menu* loadMenu4();
	static Menu* loadMenu5();
	static Menu* loadMenu6();

	const sf::Music& getMusic() const;
	void setMusic(const Musics& mus);

	void turnMusicUp();
	void turnMusicDown();

	void turnSoundsUp();
	void turnSoundsDown();

	void setGoban(const Goban& goban);
	Goban getGoban() const;

	void launchTsumego();

	const std::vector<Screen*>& getScreens() const;
	const Screens& getScreen() const;

private:
	// Screens
	std::vector<Screen*> screens;
	Screens cur_screen;

	// Musics
	std::vector<sf::Music*> musics;
	Musics cur_music;

	// Game
	Game_window* game;
};

