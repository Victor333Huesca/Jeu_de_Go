#pragma once
#include "Choice.h"

class Choice_Simple : public Choice
{
public:
	Choice_Simple(const char* name, const sf::Text& text_style, sf::Vector2f pos, std::function<Screens(sf::RenderTarget&, Go_Solver&)> _Run, sf::Vector2f scale = sf::Vector2f(1, 1));
	Choice_Simple(const char* name, const sf::Text& text_style, float posX, float posY, std::function<Screens(sf::RenderTarget&, Go_Solver&)> _Run, sf::Vector2f scale = sf::Vector2f(1, 1));
	virtual ~Choice_Simple();

	// Polymorphism
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;

	// Charge les attributs communs pour un groupe d'item (i.e. un choix ne peut vivre sans le menu auquel il appartient).
	void setFont(const sf::Font& _font);


private:
	sf::Text text;
	const sf::Font* font;
};
