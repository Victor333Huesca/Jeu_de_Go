#pragma once
#include "../Globals.h"
#include "Square.h"
#include "Timer.h"

class Infos : public sf::Drawable
{
public:
	Infos();
	~Infos();

	sf::View getView() const;
	void setCurPlayer(const Square::Value& value);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;

private:
	// Background
	sf::Texture bg_txr;
	sf::Sprite bg_spr;

	// Player turn
	sf::Texture white_turn_txr;
	sf::Texture black_turn_txr;
	sf::Sprite player_turn_spr;

	// Timers
	Timer timer_white;
	Timer timer_black;

	// View
	sf::View view;
};

