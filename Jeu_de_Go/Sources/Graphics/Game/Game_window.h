#pragma once
#include "../Globals.h"
#include "Board.h"
#include "Infos.h"
#include "../Screen.h"
#include "../../Engine/Goban.h"
#include "../../Engine/IA.h"

class Go_Solver;

class Game_window : public Screen
{
public:
	Game_window();
	~Game_window();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
	virtual Screens Run(sf::RenderWindow &App, Go_Solver& solver);

	Screens click(const sf::RenderWindow& window, sf::Vector2i pos, const sf::Mouse::Button& type = sf::Mouse::Button::Left);
	void zoom(const float delta, sf::Vector2i pos, sf::RenderWindow& window);
	Screens keyPressed(const sf::Event::KeyEvent& key);
	void setGoban(const Goban& goban);
	Goban getGoban() const;
	void setView(const sf::FloatRect& zone);
	void territoire();

	void turnSoundsUp();
	void turnSoundsDown();

private:
	Board board;
	Infos infos;
	Square::Value cur_player;
};
