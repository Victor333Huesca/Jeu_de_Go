#include "Choice.h"

Choice::Choice(sf::Vector2f pos, const char* file_blank, const char* file_hover, const char* file_selected, const char* file_clicked)
{
    // Load textures
    t_blank.loadFromFile(file_blank);
    t_hover.loadFromFile(file_hover);
    t_selected.loadFromFile(file_selected);
    t_clicked.loadFromFile(file_clicked);

    // Apply the default one
    sprite.setTexture(t_blank);
    sprite.setPosition(pos);
}

Choice::~Choice()
{
}

void Choice::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}

sf::Vector2f Choice::getSize() const
{
    return sf::Vector2f(sprite.getTextureRect().width, sprite.getTextureRect().height);
}
