#pragma once
#include "../Globals.h"
#include "Square.h"
#include "../../Engine/Goban.h"

class Board : public sf::Drawable
{
public:
	Board();
	template <typename T>
	Board(const sf::Vector2<T>& _size);
	template <typename T>
	Board(const T& x, const T& y);
	~Board();

	// Treate click event
	bool click(sf::Vector2i pos, const Square::Value& value);
	sf::View getView() const;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;

private:
	// Goban
	sf::Vector2u size;		/*!< Number of squares on the goban */
	Square** array;			/*!< Goban's intersections representation */

	// Background
	sf::Texture bg_txr;		/*!< Background texture */
	sf::Sprite bg_spr;		/*!< Background sprite */

	// Other stuff
	sf::View view;			/*!< Board's view */

	// Goban engine
	Goban engine;			/*!< Engine used by Wissem and Mamadou */

	// Return case corresponding to view's position
	bool posToSquare(sf::Vector2i& pos) const;

	// To switch between Graphics Value and Engine VAL
	static Square::Value Board::transform(const Etat::VAL & value);
	static Etat::VAL Board::transform(const Square::Value & value);
};

template <typename T>
Board::Board(const sf::Vector2<T>& _size) :
	Board()
{
	// Set size
	size = static_cast<sf::Vector2u>(_size);
	
	// Create X array
	array = new Square*[size.x];

	// Create Y array
	for (size_t i = 0; i < size.x; i++)
	{
		array[i] = new Square[size.y];
		for (size_t j = 0; j < size.y; j++)
		{
			array[i][j].setPosition(sf::Vector2f(i, j));
		}
	}
}

template <typename T>
Board::Board(const T& x, const T& y) :
	Board(sf::Vector2(x, y))
{
}