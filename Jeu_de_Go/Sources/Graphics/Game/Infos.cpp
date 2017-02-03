#include "Infos.h"



Infos::Infos() :
	view(sf::FloatRect(VIEW_INFOS_POS_X, VIEW_INFOS_POS_Y, INFOS_IMG_SIZE_X, INFOS_IMG_SIZE_Y))
{
	// Set the viewport
	view.setViewport(sf::FloatRect(
		(float)WINDOW_WIDTH / (WINDOW_WIDTH + INFOS_SIZE), 0,
		(float)INFOS_SIZE / (WINDOW_WIDTH + INFOS_SIZE), 1));

	// Load background
	bg_txr.loadFromFile("./Ressources/Img/infos_bg.png");
	bg_spr.setTexture(bg_txr);
	bg_spr.setPosition(VIEW_INFOS_POS_X, VIEW_INFOS_POS_Y);

	// Load player textures
	white_turn_txr.loadFromFile("./Ressources/Img/infos_white.png");
	black_turn_txr.loadFromFile("./Ressources/Img/infos_black.png");
	player_turn_spr.setTexture(white_turn_txr);
	player_turn_spr.setPosition(VIEW_INFOS_POS_X + INFOS_TURN_POS.x, VIEW_INFOS_POS_Y + INFOS_TURN_POS.y);

	// Timers - 1st load a font
	if (!Timer::initFont("./Ressources/Font/time.ttf"))
	{
		std::cerr << "Impossible de lire la police de caractere !\n";
	}

	// White
	timer_white.setPosition(sf::Vector2f(
		INFOS_TIMER_POS_WHITE.x + VIEW_INFOS_POS_X,
		INFOS_TIMER_POS_WHITE.y + VIEW_INFOS_POS_Y));
	timer_white.setFillColor(sf::Color::Black);
	timer_white.setCharacterSize(INFOS_TIMER_SIZE);
	timer_white.applyFont();

	// Black
	timer_black.setPosition(sf::Vector2f(
		INFOS_TIMER_POS_BLACK.x + VIEW_INFOS_POS_X,
		INFOS_TIMER_POS_BLACK.y + VIEW_INFOS_POS_Y));
	timer_black.setFillColor(sf::Color::Black);
	timer_black.setCharacterSize(INFOS_TIMER_SIZE);
	timer_black.applyFont();
}


Infos::~Infos()
{
}

sf::View Infos::getView() const
{
	return view;
}

void Infos::setCurPlayer(const Square::Value & value)
{
	if (value == Square::White)
	{
		player_turn_spr.setTexture(white_turn_txr);
		timer_black.pause();
		timer_white.play();
	}
	else
	{
		player_turn_spr.setTexture(black_turn_txr);
		timer_white.pause();
		timer_black.play();
	}
}


void Infos::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	// Menu name
	target.draw(bg_spr, states);

	// Player turn
	target.draw(player_turn_spr, states);

	// Timers
	target.draw(timer_white, states);
	target.draw(timer_black, states);
}
