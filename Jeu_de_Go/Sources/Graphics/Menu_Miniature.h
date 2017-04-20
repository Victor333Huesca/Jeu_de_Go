#pragma once
#include "Menu.h"
#include "Choice_miniature.h"

class Menu_Miniature : public Menu
{
public:
	Menu_Miniature(const sf::Vector2f& position, const char* texture, const Screens& _previous, const sf::Vector2f& scale = sf::Vector2f(1, 1));
	virtual ~Menu_Miniature();

	// Applique la texture et la police à chaque item
	virtual void setItemsTextures(const char* selected, const char* hover = nullptr);

private:
	sf::Texture button_selected;
	sf::Texture button_hover;

};

