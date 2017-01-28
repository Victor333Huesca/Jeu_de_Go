#pragma once
#include "Globals.h"

class Infos : public sf::Drawable
{
public:
	Infos();
	~Infos();

	sf::View getView() const;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;

private:
	// Name
	sf::Texture name_t;
	sf::Sprite name_s;

	// Player turn
	sf::Text player_turn;

	// Timers
	sf::Clock timer_white;
	sf::Clock timer_black;

	// Timers aspect
	sf::Vector2f timer_pos_w;
	sf::Vector2f timer_pos_b;
	sf::Font timer_font;
	unsigned timer_size;
	sf::Text::Style timer_style;
	sf::Color timer_color;

	sf::View view;
};

