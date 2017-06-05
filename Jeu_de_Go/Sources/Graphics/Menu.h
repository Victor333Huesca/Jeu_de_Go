#pragma once
#include "Screen.h"
#include "Choice.h"
#include "Globals.h"
#include <vector>
#include <SFML/Graphics.hpp>

class Go_Solver;

class Menu: public Screen
{
public:
    Menu(const sf::Vector2f& position, const char* texture, const Screens& _previous, const sf::Vector2f& scale = sf::Vector2f(1, 1));
    virtual ~Menu();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
    virtual Screens Run(sf::RenderWindow &window, Go_Solver& solver);

    sf::Vector2f getSize() const;
    sf::Vector2f getPosition() const;

	// Ajoute un item au menu
	virtual void addItem(const Choice& item);
	void setPrevious(const Screens& sc);

	// Debugg
	virtual void showAdresses() const;

private:
    // G�re les interactions utilisateur (sont appell�es depuis le Run
	Screens click(const sf::Mouse::Button& type, sf::RenderWindow& window, Go_Solver& solver);		// Renvoie la fenetre � charger et NO_CHANGE sinon 
	Screens mouseMoved(const sf::RenderWindow& window, sf::Vector2i pos);				// S�lectionne le menu corresponant � la nouvelle position souris.
	Screens keyPressed(const sf::Event::KeyEvent& key);								// S�lectionne le menu corresponant � l'action utilisateur


protected:
    // Options
	std::vector<std::reference_wrapper<Choice>> choices;
	Choice* cur_choice;

private:
    // Background
    sf::Sprite s_background;
    sf::Texture t_background;
	Screens previous;	
};
