#pragma once
#include "Screen.h"
#include "Choice.h"
#include "Globals.h"
#include <vector>
#include <SFML/Graphics.hpp>

class Menu: public Screen
{
public:
    Menu(const sf::Vector2f& position, sf::Vector2f& scale, const char* texture_path);
    ~Menu();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
    virtual int Run(sf::RenderWindow &window);

    sf::Vector2f getSize() const;
    sf::Vector2f getPosition() const;


    // Gère les interactions utilisateur
    void click(const sf::Mouse::Button& type, const sf::RenderWindow& window);
    void mouseMoved(const sf::RenderWindow& window, sf::Vector2i pos);
	void keyPressed(const sf::Event::KeyEvent& key);

	void addItem(Choice item);

private:
    // Options
    std::vector<Choice> choices;
    std::vector<Choice>::iterator cur_choice;

    // Background
    sf::Sprite s_background;
    sf::Texture t_background;
};
