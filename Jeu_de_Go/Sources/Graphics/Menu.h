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
    Menu(const sf::Vector2f& position, const char* texture, const sf::Vector2f& scale = sf::Vector2f(1, 1));
    ~Menu();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
    virtual int Run(sf::RenderWindow &window);

    sf::Vector2f getSize() const;
    sf::Vector2f getPosition() const;

	// Ajoute un item au menu
	virtual void addItem(Choice& item);

	// Debugg
	void showAdresses() const;

private:
    // Gère les interactions utilisateur (sont appellées depuis le Run
    int click(const sf::Mouse::Button& type, const sf::RenderWindow& window);		// Renvoie la fenetre à charger et NO_CHANGE sinon 
    void mouseMoved(const sf::RenderWindow& window, sf::Vector2i pos);				// Sélectionne le menu corresponant à la nouvelle position souris.
	void keyPressed(const sf::Event::KeyEvent& key);								// Sélectionne le menu corresponant à l'action utilisateur


protected:
    // Options
	std::vector<std::reference_wrapper<Choice>> choices;
	Choice* cur_choice;

private:
    // Background
    sf::Sprite s_background;
    sf::Texture t_background;
};
