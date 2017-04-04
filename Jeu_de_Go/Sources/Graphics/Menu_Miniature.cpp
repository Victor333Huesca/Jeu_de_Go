#include "Menu_Miniature.h"



Menu_Miniature::Menu_Miniature(const sf::Vector2f & position, const char * texture, const sf::Vector2f & scale) :
	Menu(position, texture, scale)
{

}

Menu_Miniature::~Menu_Miniature()
{
	Menu::~Menu();
}

void Menu_Miniature::setItemsTextures(const char * selected, const char * hover)
{
	// Load textures
	button_selected.loadFromFile(selected);
	if (hover != nullptr)	button_hover.loadFromFile(hover);
	else button_hover.loadFromFile(selected);

	// Apply to each choice
	for (Choice& c : choices)
		c.loadTextures(nullptr, &button_selected, &button_hover);
}
