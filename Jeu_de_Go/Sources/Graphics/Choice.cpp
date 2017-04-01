#include "Choice.h"
#include <iostream>

Choice::Choice(const char* name, const sf::Text& text_style, sf::Vector2f pos, sf::Vector2f scale) :
	selected(false),
	t_blank(nullptr),
	t_selected(nullptr)
{
    // Set Common
    sprite.setPosition(pos);
	sprite.setScale(scale);

	// Set the text
	text = text_style;
	text.setString(name);
	text.setPosition(pos.x, pos.y + 20);
}

Choice::Choice(const char * name, const sf::Text & text_style, float posX, float posY, sf::Vector2f scale) :
	Choice(name, text_style, sf::Vector2f(posX, posY), scale)
{

}

Choice::~Choice()
{
}

void Choice::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states);
	target.draw(text, states);
}

sf::Vector2f Choice::getSize() const
{
    return sf::Vector2f(sprite.getTextureRect().width, sprite.getTextureRect().height);
}

bool Choice::isSelected() const
{
	return selected;
}

void Choice::move(const sf::Vector2f & offset)
{
	sprite.move(offset);
}

void Choice::loadTextures(const sf::Texture & blank, const sf::Texture & selected)
{
	// Set texutes
	t_blank = &blank;
	t_selected = &selected;

	// Apply the one should be
	sprite.setTexture(*t_blank, true);
}

void Choice::setFont(const sf::Font & font)
{
	text.setFont(font);
}

std::string Choice::getName() const
{
	return text.getString().toAnsiString();
}

const sf::Texture* Choice::getTextureAdress() const
{
	return t_blank;
}
