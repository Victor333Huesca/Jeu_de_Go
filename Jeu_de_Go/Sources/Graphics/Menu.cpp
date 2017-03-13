#include "Menu.h"

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(s_background);

    for (auto choice : choices)
        target.draw(choice, states);
}
