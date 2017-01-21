#pragma once
#include <SFML\Graphics.hpp>

enum Square_value
{
	Black,
	White,
	None,
	Forbiden
};

class Board
{
public:
	Board(sf::RenderWindow& window = sf::RenderWindow());
	template <typename T>	Board(const sf::Vector2<T> _size, sf::RenderWindow& window = sf::RenderWindow());
	template <typename T>	Board(const T x, const T y, sf::RenderWindow& window = sf::RenderWindow());
	~Board();

private:
	sf::Vector2u size;
	Square_value** array;
	sf::RenderWindow& board_window;
};




// Include following in a separate file
template<typename T>
inline Board::Board(const sf::Vector2<T> _size, sf::RenderWindow& window = sf::RenderWindow()) :
	size(static_cast<unsigned>(_size)),
	board_window(),
	board_window(window)
{
	array = new Square_value[size.x];
	for (size_t i = 0; i < size.x; i++)
	{
		array[i] = new Square_value[size.y];
	}
}

template<typename T>
inline Board::Board(const T x, const T y, sf::RenderWindow& window = sf::RenderWindow()) :
	Board(sf::Vector2(x, y), window)
{
}
