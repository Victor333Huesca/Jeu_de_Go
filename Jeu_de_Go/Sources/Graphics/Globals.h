#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <cassert>
#include <stdexcept>


#ifdef _WIN32
#define CLEAR_CMD "cls"
#else
#define CLEAR_CMD "clear"
#endif // _WIN32

#define SQUARE_WIDTH 144
#define SQUARE_HEIGHT 144

#define NB_SQUARES_X 19
#define NB_SQUARES_Y 19

#define OFFSET_X_B -2
#define OFFSET_Y_B -2

#define OFFSET_X_E -2
#define OFFSET_Y_E -2

#define INFOS_SIZE 200

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

#define BOARD_WIDTH SQUARE_WIDTH * NB_SQUARES_X + OFFSET_X_B + OFFSET_X_E	// 452
#define BOARD_HEIGHT SQUARE_HEIGHT * NB_SQUARES_Y + OFFSET_Y_B + OFFSET_Y_E	// 452

#define VIEW_BOARD_POS_X 10000
#define VIEW_BOARD_POS_Y 10000

#define VIEW_INFOS_POS_X -10000
#define VIEW_INFOS_POS_Y -10000

#define INFOS_IMG_SIZE_X 1000
#define INFOS_IMG_SIZE_Y WINDOW_HEIGHT * (WINDOW_WIDTH + INFOS_SIZE) / INFOS_SIZE

#define INFOS_TURN_POS sf::Vector2f(320, 1470)
#define INFOS_TURN_SIZE sf::Vector2f(353, 90)

#define INFOS_TIMER_POS_WHITE sf::Vector2f(430, 2400)
#define INFOS_TIMER_POS_BLACK sf::Vector2f(520, 2500)
#define INFOS_TIMER_SIZE 100

// Declare globals variables here
extern std::ofstream log_file;

#define __ERROR_LEVEL__ 100

// Here are the differents screens
enum Screens
{
	// Game modes
	GAME = 8,

	// Menus
	MAIN_MENU = 1,
	PROBLEMS_MENU = 2,
	OPTIONS_MENU = 3,
	AUDIO = 5,
	VIDEO = 6,
	PAUSE = 7,


	// Other
	CONTINUE = 0,
	EXIT = -1,
	PREVIOUS = -33,
	NO_CHANGE = -777,
	ERROR = -34
};