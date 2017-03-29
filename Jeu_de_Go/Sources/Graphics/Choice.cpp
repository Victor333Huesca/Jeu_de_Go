#include "Choice.h"
#include <iostream>

Choice::Choice(const char* name, const sf::Text& text_style, sf::Vector2f pos, sf::Vector2f sc, const char* t) :
	selected(false)
{
	sf::Texture te;
	if (!te.loadFromFile("./Ressources/Img/button_blank.png"))
		std::cout << "erreur lors de l'ouvertur du fichier" << std::endl;
	sprite.setTexture(te);
    // Set Common
    sprite.setPosition(pos);
	sprite.setScale(sc);

	// Set the text
	text = text_style;
	text.setString(name);
	text.setPosition(pos.x, pos.y + 20);
}

Choice::Choice(const char * name, const sf::Text & text_style, float posX, float posY, sf::Vector2f sc, const char* t) :
	Choice(name, text_style, sf::Vector2f(posX, posY), sc, t)
{

}

Choice::~Choice()
{
}

void Choice::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states);
	//target.draw(text, states);
}

sf::Vector2f Choice::getSize() const
{
    return sf::Vector2f(sprite.getTextureRect().width, sprite.getTextureRect().height);
}

void Choice::move(const sf::Vector2f & offset)
{
	sprite.move(offset);
}

void Choice::loadTextures(const sf::Texture & blank, const sf::Texture & selected)
{
	t_blank = &blank;
	t_selected = &selected;

	sprite.setTexture(*t_blank, true);

	std::cout << text.getString().toAnsiString() << " : (" << sprite.getPosition().x << ", " << sprite.getPosition().y << ")   -->   ";
	std::cout << "Texture's size : (" << t_blank->getSize().x << ", " << t_blank->getSize().y << ")" << std::endl;
}
