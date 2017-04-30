#pragma once
#include <SFML/Graphics.hpp>
#include "Globals.h"
//#include "Screens.h"

class Go_Solver;

class Screen : public sf::Drawable
{
public :
    virtual Screens Run(sf::RenderWindow &window, Go_Solver& solver) = 0;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const = 0;

};
