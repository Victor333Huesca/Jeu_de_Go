#include "Infos.h"



Infos::Infos() :
	view(sf::FloatRect(-1000, -1000, 
		(SQUARE_HEIGHT * NB_SQUARES_X + OFFSET_X_B * 2) * INFOS_SIZE, 
		SQUARE_HEIGHT * NB_SQUARES_Y + OFFSET_Y_B * 2))
{
	//name_t.loadFromFile("menu_info_title.png");

	view.setViewport(sf::FloatRect(1 - INFOS_SIZE, 0, INFOS_SIZE, 1));
}


Infos::~Infos()
{
}

sf::View Infos::getView() const
{
	return view;
}


void Infos::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	// Menu name
	target.draw(name_s, states);

	// Player turn
	target.draw(player_turn, states);

	// Timers
	sf::Text timer;

	// White
	timer.setString(
		"White : " +
		std::to_string(timer_white.getElapsedTime().asSeconds()) +
		" s !");
	timer.setPosition(timer_pos_w);

	target.draw(timer, states);
}
