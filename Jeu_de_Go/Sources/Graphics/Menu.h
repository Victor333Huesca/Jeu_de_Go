#pragma once
#include "Screen.h"
#include "Choice.h"
#include "Globals.h"
#include <vector>
#include <SFML/Graphics.hpp>

#define NO_CHANGE -777

class Menu: public Screen
{
public:
    Menu(const sf::Vector2f& position, const char* texture, const char* font, sf::Vector2f& scale);
    ~Menu();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
    virtual int Run(sf::RenderWindow &window);

    sf::Vector2f getSize() const;
    sf::Vector2f getPosition() const;


    // Gère les interactions utilisateur
    int click(const sf::Mouse::Button& type, const sf::RenderWindow& window);		// Renvoie la fenetre à charger et NO_CHANGE sinon 
    void mouseMoved(const sf::RenderWindow& window, sf::Vector2i pos);				// Sélectionne le menu corresponant à la nouvelle position souris.
	void keyPressed(const sf::Event::KeyEvent& key);								// Sélectionne le menu corresponant à l'action utilisateur

	void addItem(Choice& item);														// Ajoute un item au menu

	void setItemsTextures(const char* blank, const char* selected);					// Applique la texture à chaque item

private:
    // Options
    std::vector<Choice> choices;
    //std::vector<Choice>::iterator cur_choice;
	Choice* cur_choice;

    // Background
    sf::Sprite s_background;
    sf::Texture t_background;

	// Choices
	sf::Texture button_blank;
	sf::Texture button_selected;
	sf::Font text_font;
};
