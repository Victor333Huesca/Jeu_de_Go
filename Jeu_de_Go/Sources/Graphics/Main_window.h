#pragma once
#include "Globals.h"
#include "Game/Game_window.h"

class Main_window : public sf::RenderWindow
{
public:
	Main_window();
	Main_window(
		sf::VideoMode mode,
		const sf::String& title,
		sf::Uint32 style = sf::Style::Default,
		const sf::ContextSettings& settings = sf::ContextSettings());
	~Main_window();

	// Just an interface for the game_window's click methode
	void click(sf::Vector2i pos, const sf::Mouse::Button& type = sf::Mouse::Button::Left);
	void zoom(const float delta, const sf::Vector2i& pos);

	void draw();
	void draw(const sf::Drawable& drawable, const sf::RenderStates&	states = sf::RenderStates::Default);

private:
	// Privates Attributes
	Game_window game_window;
	sf::View main_view;
};
