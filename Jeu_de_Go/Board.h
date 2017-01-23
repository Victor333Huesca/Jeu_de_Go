#pragma once
#include <SFML\Graphics.hpp>
#include "Square.h"

class Board
{
public:
	Board(sf::RenderWindow& window = sf::RenderWindow());
	template <typename T>
	Board(const sf::Vector2<T>& _size, sf::RenderWindow& window = sf::RenderWindow());
	template <typename T>
	Board(const T& x, const T& y, sf::RenderWindow& window = sf::RenderWindow());
	~Board();

	sf::RenderWindow& getWindow();
	void draw();

private:
	sf::Vector2u size;
	Square** array;
	sf::RenderWindow& window;

	// Background
	sf::Texture bg_txr;		/*!< Background texture */
	sf::Sprite bg_spr;		/*!< Background sprite */

};

template <typename T>
Board::Board(const sf::Vector2<T>& _size, sf::RenderWindow& _window) :
	Board(_window)
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
Board::Board(const T& x, const T& y, sf::RenderWindow& _window) :
	Board(sf::Vector2(x, y), _window)
{
}