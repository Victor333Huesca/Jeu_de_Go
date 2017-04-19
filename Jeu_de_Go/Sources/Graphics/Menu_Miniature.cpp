#include "Menu_Miniature.h"



Menu_Miniature::Menu_Miniature(const sf::Vector2f & position, const char * texture, const Screens& _previous, const sf::Vector2f & scale) :
	Menu(position, texture, _previous, scale)
{
#if __ERROR_LEVEL__ > 0
	log_file << "Menu_Miniature::Menu_Miniature(), ";
#endif // __ERROR_LEVEL__ > 0
}

Menu_Miniature::~Menu_Miniature()
{
#if __ERROR_LEVEL__ > 0
	log_file << "Menu_Miniature::~Menu_Miniature(), ";
#endif // __ERROR_LEVEL__ > 0
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

#if __ERROR_LEVEL__ > 0
	log_file << "Menu_Miniature::setItemTextures(), ";
#endif // __ERROR_LEVEL__ > 0
}
