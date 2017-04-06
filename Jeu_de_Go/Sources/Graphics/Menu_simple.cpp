#include "Menu_simple.h"


Menu_simple::Menu_simple(const sf::Vector2f & position, const char * texture, const sf::Vector2f & scale) :
	Menu(position, texture, scale)
{
#if __ERROR_LEVEL__ > 0
	log_file << "Menu_simple::Menu_simple(), ";
#endif // __ERROR_LEVEL__ > 0
}

Menu_simple::~Menu_simple()
{
#if __ERROR_LEVEL__ > 0
	log_file << "Menu_simple::~Menu_simple(), ";
#endif // __ERROR_LEVEL__ > 0
}

void Menu_simple::setItemsTextures(const char * blank, const char * selected, const char * hover)
{
	// Load textures
	button_blank.loadFromFile(blank);
	button_selected.loadFromFile(selected);
	if (hover != nullptr)	button_hover.loadFromFile(hover);
	else button_hover.loadFromFile(selected);

	// Apply to each choice
	for (Choice& c : choices)
		c.loadTextures(&button_blank, &button_selected, &button_hover);

#if __ERROR_LEVEL__ > 0
	log_file << "Menu_simple::setItemTextures(), ";
#endif // __ERROR_LEVEL__ > 0
}

void Menu_simple::setItemsFonts(const char * font)
{
	text_font.loadFromFile(font);

#if __ERROR_LEVEL__ > 0
	log_file << "Menu_simple::setItemFonts(), ";
#endif // __ERROR_LEVEL__ > 0
}

void Menu_simple::addItem(Choice_Simple & item)
{
	item.setFont(text_font);
	
	Choice_Simple* _item = new Choice_Simple(item);
	choices.push_back(*_item);

#if __ERROR_LEVEL__ > 0
	log_file << "Menu_simple::addItem(), ";
#endif // __ERROR_LEVEL__ > 0
}
