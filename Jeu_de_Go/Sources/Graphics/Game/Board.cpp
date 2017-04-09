#include "Board.h"

Board::Board() :
	size(),
	array(nullptr),
	bg_txr(),
	bg_spr(),
	view(sf::FloatRect(VIEW_BOARD_POS_X, VIEW_BOARD_POS_Y, BOARD_WIDTH, BOARD_HEIGHT)),
	view_origin(view)
{
	// Initialise squares's textures
	Square::loadTextures();

	// Load background
	bg_txr.loadFromFile("./Ressources/Img/background3.png");
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

bool Board::click(sf::Vector2i pos, const Square::Value & value, const sf::Mouse::Button& event)
{
	// Result of the click event
	bool result(false);

	if (event == sf::Mouse::Button::Left)
	{
		// Left click

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

					system(CLEAR_CMD);

					//DEFINE GROUPS
					engine.rechercheGroupes();
					engine.afficheGroupes(std::cout);
					//ELIMINATE GROUPS
					engine.eliminateOppGroups(transform(value));
					// Change square's value
					load();

					// Display some debugg features
					//std::cout << engine << std::endl;

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
	}

	return result;
}

void Board::zoom(const float delta, const sf::Vector2i& pos)
{
	if (delta > 0)
	{
		// Zoom in if the view isn't currently at its minimum
		if (view.getSize().x > view_origin.getSize().x / ZOOM_FACTOR)
		{
			// Zoom in
			view.zoom(delta - 0.1f);

			// Fix zoom overflow
			if (view.getSize().x < view_origin.getSize().x / ZOOM_FACTOR)
			{
				view.setSize(view_origin.getSize().x / ZOOM_FACTOR, view_origin.getSize().y / ZOOM_FACTOR);
			}

			// Move camera
			view.setCenter(static_cast<sf::Vector2f>(pos));

			// Fix movement overflow
			viewBound();
		}
	}
	else
	{
		// Zoom out if the view isn't currently at its maximum
		if (view.getSize().x < view_origin.getSize().x)
		{
			// Zoom out
			view.zoom(-delta + 0.1f);

			// Fix overflow
			if (view.getSize().x > view_origin.getSize().x)
			{
				view.setSize(view_origin.getSize().x, view_origin.getSize().y);
			}

			// Move camera
			view.setCenter(static_cast<sf::Vector2f>(pos));

			// Fix movement overflow
			viewBound();
		}
	}
}

void Board::cancel()
{
	if (engine.cancel())
	{
		load();
	}
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

void Board::load()
{
	for (size_t i = 0; i < NB_SQUARES_X; i++)
	{
		for (size_t j = 0; j < NB_SQUARES_Y; j++)
		{
			array[i][j].setValue(transform(engine.coord(i, j).getVal()));
		}
	}
}

void Board::load(const Goban & copy)
{
	engine = copy;
	load();
}

Goban Board::getGoban() const
{
	return engine;
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

Square::Value Board::transform(const Etat::VAL & value)
{
	Square::Value tmp = Square::None;
	switch (value)
	{
	case Etat::BLANC:
		tmp = Square::White;
		break;
	case Etat::NOIR:
		tmp = Square::Black;
		break;
	case Etat::VIDE:
	case Etat::KOWHITE:
	case Etat::KOBLACK:
		tmp = Square::None;
		break;
	default:
		break;
	}

	return tmp;
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

void Board::viewBound()
{
	sf::Vector2f offset;

	const sf::FloatRect pos(
		view.getCenter().x - view.getSize().x / 2,
		view.getCenter().y - view.getSize().y / 2,
		view.getSize().x, view.getSize().y);

	const sf::FloatRect pos_ori(
		view_origin.getCenter().x - view_origin.getSize().x / 2,
		view_origin.getCenter().y - view_origin.getSize().y / 2,
		view_origin.getSize().x, view_origin.getSize().y);

	if (pos.left < pos_ori.left)
	{
		offset.x = pos_ori.left - pos.left;
	}
	else if (pos.left + pos.width > pos_ori.left + pos_ori.width)
	{
		offset.x = (pos_ori.left + pos_ori.width) - (pos.left + pos.width);
	}

	if (pos.top < pos_ori.top)
	{
		offset.y = pos_ori.top - pos.top;
	}
	else if (pos.top + pos.height > pos_ori.top + pos_ori.height)
	{
		offset.y = (pos_ori.top + pos_ori.height) - (pos.top + pos.height);
	}

	view.move(offset);
}
