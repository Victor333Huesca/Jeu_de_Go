#include "Main_window.h"



Main_window::Main_window() :
	sf::RenderWindow(),
	game_window(),
	default_view()
{
}

Main_window::Main_window(sf::VideoMode mode, const sf::String & title, sf::Uint32 style, const sf::ContextSettings & settings) :
	sf::RenderWindow(mode, title, style, settings),
	game_window(),
	default_view()
{
}


Main_window::~Main_window()
{
}

void Main_window::click(sf::Vector2i pos, const sf::Mouse::Button & type)
{
	// Look in which menu was the mouse
	if (pos.x < WINDOW_WIDTH)
	{
		game_window.click(*this, pos, type);
	}
	else
	{
	}
}

void Main_window::draw()
{
	draw(game_window);
}

void Main_window::draw(const sf::Drawable & drawable, const sf::RenderStates & states)
{
	sf::RenderWindow::draw(drawable, states);
}
