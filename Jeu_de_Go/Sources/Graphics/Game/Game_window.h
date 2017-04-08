#pragma once
#include "../Globals.h"
#include "Board.h"
#include "Infos.h"
#include "../../Engine/Arbre.h"
#include "../Screen.h"
#include "../../Engine/Goban.h"

class Game_window : public Screen
{
public:
	Game_window();
	~Game_window();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
	virtual int Run(sf::RenderWindow &App, Game_window&);

	void click(const sf::RenderWindow& window, sf::Vector2i pos, const sf::Mouse::Button& type = sf::Mouse::Button::Left);
	void zoom(const float delta, sf::Vector2i pos, sf::RenderWindow& window);
	void keyPressed(const sf::Event::KeyEvent& key);
	void setGoban(const Goban goban);
	void territoire();

private:
	Board board;
	Infos infos;
	Square::Value cur_player;
};
