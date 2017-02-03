#pragma once
#include "../Globals.h"

class Timer : public sf::Clock, public sf::Text
{
public:
	Timer();
	Timer(
		const sf::Vector2f& _position,
		const unsigned& _size,
		const sf::Color& _color,
		const sf::Text::Style& _style = sf::Text::Style(),
		const sf::Font& _font = sf::Font());
	~Timer();

	static bool initFont(const sf::String& _font);
	void applyFont();
	void pause();
	void play();
	void restart();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;

private:
	static sf::Font font;
	sf::Time time;
	bool isPaused;
};

