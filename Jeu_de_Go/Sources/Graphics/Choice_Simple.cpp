#include "Choice_Simple.h"


Choice_Simple::Choice_Simple(const char * name, const sf::Text & text_style, sf::Vector2f pos, std::function<int(const sf::RenderTarget&window)> _Run, sf::Vector2f scale) :
	Choice(pos, _Run, scale)
{
	text = text_style;
	text.setString(name);
	text.setPosition(pos.x + 20, pos.y + -8);
}

Choice_Simple::Choice_Simple(const char * name, const sf::Text & text_style, float posX, float posY, std::function<int(const sf::RenderTarget&window)> _Run, sf::Vector2f scale) :
	Choice_Simple(name, text_style, sf::Vector2f(posX, posY), _Run, scale)
{
}

Choice_Simple::~Choice_Simple()
{
}

void Choice_Simple::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	Choice::draw(target, states);
	target.draw(text, states);
}

void Choice_Simple::setFont(const sf::Font & _font)
{
	font = &_font;
	text.setFont(*font);
}
