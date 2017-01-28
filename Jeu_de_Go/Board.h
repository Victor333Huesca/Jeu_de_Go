#pragma once
#include "Globals.h"
#include "Square.h"

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
	void click(sf::Vector2i pos, const Square::Value& value);
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

	// Return case corresponding to view's position
	sf::Vector2i getSquareAt(sf::Vector2i pos) const;
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