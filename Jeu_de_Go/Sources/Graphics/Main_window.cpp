#include "Main_window.h"



Main_window::Main_window() :
	sf::RenderWindow(),
	game_window(),
	main_view()
{
}

Main_window::Main_window(sf::VideoMode mode, const sf::String & title, sf::Uint32 style, const sf::ContextSettings & settings) :
	sf::RenderWindow(mode, title, style, settings),
	game_window(),
	main_view()
{
}


Main_window::~Main_window()
{
}

void Main_window::click(sf::Vector2i pos, const sf::Mouse::Button & type)
{
	game_window.click(*this, pos, type);
}

void Main_window::zoom(const float delta, const sf::Vector2i& pos)
{
	game_window.zoom(delta, pos, *this);
}

void Main_window::draw()
{
	draw(game_window);
}

void Main_window::draw(const sf::Drawable & drawable, const sf::RenderStates & states)
{
	sf::RenderWindow::draw(drawable, states);
}
