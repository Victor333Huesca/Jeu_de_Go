#include "Timer.h"

sf::Font Timer::font = sf::Font();

Timer::Timer() :
	sf::Clock(),
	sf::Text(),
	time(),
	isPaused(false)
{
}

Timer::Timer(const sf::Vector2f & position, const unsigned & size, const sf::Color & color, const sf::Text::Style & style, const sf::Font & font) :
	Timer()
{
	setPosition(position);
	setFont(font);
	setCharacterSize(size);
	setFillColor(color);
	setStyle(style);
}

Timer::~Timer()
{
}

bool Timer::initFont(const sf::String & _font)
{
	return font.loadFromFile(_font);
}

void Timer::applyFont()
{
	setFont(font);
}

void Timer::pause()
{
	time += getElapsedTime();
	isPaused = true;
}

void Timer::play()
{
	sf::Clock::restart();
	isPaused = false;
}

void Timer::restart()
{
	time = sf::Time::Zero;
	sf::Clock::restart();
}

void Timer::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	// Copy itself
	sf::Text tmp_txt(*this);

	// Get time
	sf::Time tmp_time(time);

	// Add time if not paused
	tmp_time += isPaused ? sf::Time::Zero : getElapsedTime();

	// Set up the string corresponding to the time in second
	tmp_txt.setString(std::to_string((int)tmp_time.asSeconds()) + " s");

	// Then draw
	target.draw(tmp_txt, states);
}
