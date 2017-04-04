#pragma once
#include "Menu.h"
#include "Choice_Simple.h"

class Menu_simple : public Menu
{
public:
	Menu_simple(const sf::Vector2f& position, const char* texture, const sf::Vector2f& scale = sf::Vector2f(1, 1));
	~Menu_simple();

	// Applique la texture et la police à chaque item
	virtual void setItemsTextures(const char* blank, const char* selected ,const char* hover = nullptr);
	virtual void setItemsFonts(const char* font);

	// Ajoute un item au menu
	virtual void addItem(Choice_Simple& item);


private:
	sf::Texture button_blank;
	sf::Texture button_selected;
	sf::Texture button_hover;
	sf::Font text_font;
};
