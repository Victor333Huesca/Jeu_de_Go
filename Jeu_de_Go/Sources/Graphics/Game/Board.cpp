#include "Board.h"

Board::Board() :
	size(),
	array(nullptr),
	bg_txr(),
	bg_spr(),
	view(sf::FloatRect(VIEW_BOARD_POS_X, VIEW_BOARD_POS_Y, BOARD_WIDTH, BOARD_HEIGHT))
{
	// Initialise squares's textures
	Square::loadTextures();

	// Load background
	bg_txr.loadFromFile("./Ressources/Img/background2.png");
	bg_spr.setTexture(bg_txr);
	bg_spr.setPosition(sf::Vector2f(VIEW_BOARD_POS_X, VIEW_BOARD_POS_X));

	// Set viewport
	view.setViewport(sf::FloatRect(0, 0, (float)WINDOW_WIDTH / (WINDOW_WIDTH + INFOS_SIZE), 1));
}

Board::~Board()
{
	for (size_t i = 0; i < size.x; i++)
	{
		delete[] array[i];
	}
	delete[] array;
}

bool Board::click(sf::Vector2i pos, const Square::Value & value)
{
	// Result of the click event
	bool result(false);

	pos.x -= VIEW_BOARD_POS_X;
	pos.y -= VIEW_BOARD_POS_Y;

	// Check that user has clicked on the board	and not on board's boarder
	if (pos.x >= OFFSET_X_B &&
		pos.y >= OFFSET_Y_B &&
		pos.x < BOARD_WIDTH - OFFSET_X_E &&
		pos.y < BOARD_HEIGHT - OFFSET_Y_E)
	{
		// Get square at the position demanded
		if (posToSquare(pos))
		{
			// We have a correct square at pos so inform engine
			if (engine.move(transform(value), pos.x, pos.y))
			{
				// Move has been allowed
				result = true;

				// Change square's value
				array[pos.x][pos.y].setValue(value);

				// Display some debugg features
				//std::cout << engine << std::endl;
				system("cls");
				engine.rechercheGroupes();
				engine.afficheGroupes();
				std::cout << std::endl;
			}
		}
		else
		{
			// Position wasn't on an intersection
			result = false;
		}
	}
	else
	{
		// Board's boarder
		result = false;
	}
	
	return result;
}

sf::View Board::getView() const
{
	return view;
}

bool Board::posToSquare(sf::Vector2i& pos) const
{
	sf::Vector2i tmp;

	// Get the square's corresponding position
	tmp.x = (pos.x - OFFSET_X_B) / SQUARE_HEIGHT;
	tmp.y = (pos.y - OFFSET_Y_B) / SQUARE_HEIGHT;

	// Check if it's a valid square
	if (tmp.x >= 0 && tmp.y >= 0 && tmp.x < NB_SQUARES_X && tmp.y < NB_SQUARES_Y)
	{
		// It is
		pos = tmp;
		return true;
	}
	else
	{
		return false;
	}
}

void Board::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	// Draw background
	target.draw(bg_spr, states);

	// Draw each square
	for (size_t i = 0; i < size.x; i++)
	{
		for (size_t j = 0; j < size.y; j++)
		{
			array[i][j].draw(target, states);
		}
	}
}

Etat::VAL Board::transform(const Square::Value & value)
{
	Etat::VAL tmp;
	switch (value)
	{
	case Square::Black:
		tmp = Etat::NOIR;
		break;
	case Square::White:
		tmp = Etat::BLANC;
		break;
	case Square::None:
		tmp = Etat::VIDE;
		break;
	default:
		break;
	}

	return tmp;
}

Square::Value Board::transform(const Etat::VAL & value)
{
	Square::Value tmp;
	switch (value)
	{
	case Etat::BLANC:
		tmp = Square::White;
		break;
	case Etat::NOIR:
		tmp = Square::Black;
		break;
	case Etat::VIDE:
	case Etat::KO:
		tmp = Square::None;
		break;
	default:
		break;
	}

	return tmp;
}
