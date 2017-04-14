#pragma once
#include <SFML/Graphics.hpp>
#include "Globals.h"
//#include "Screens.h"

class Game_window;

class Screen : public sf::Drawable
{
public :
    virtual Screens Run(sf::RenderWindow &window, Game_window&) = 0;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const = 0;
};
