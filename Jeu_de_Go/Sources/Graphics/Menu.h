#pragma once
#include "Screen.h"
#include "Choice.h"
#include <vector>
#include <SFML/Graphics.hpp>

class Menu: public Screen
{
public:
    Menu();
    ~Menu();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;

private:
    // Size, position, etc...
    sf::Vector2f size;

    // Options
    std::vector<Choice> choices;
    std::vector<Choice>::iterator cur_choice;

    // Background
    sf::Sprite s_background;
    sf::Texture t_background;
};
