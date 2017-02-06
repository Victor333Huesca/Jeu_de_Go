#pragma once
#include "../Globals.h"
#include "Board.h"
#include "Infos.h"

class Game_window : public sf::Drawable
{
public:
	Game_window();
	~Game_window();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;

	void click(const sf::RenderWindow& window, sf::Vector2i pos, const sf::Mouse::Button& type = sf::Mouse::Button::Left);

private:
	Board board;
	Infos infos;
	Square::Value cur_player;
};

