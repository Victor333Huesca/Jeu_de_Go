#pragma once
#include <SFML/Graphics.hpp>

class Choice: public sf::Drawable
{
public:
    Choice(sf::Vector2f pos,
        const char* file_blank,
        const char* file_hover,
        const char* file_selected,
        const char* file_clicked);
    ~Choice();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
    sf::Vector2f getSize() const;

private:
    // Somes infos
    bool selected;
    bool hover;

    // Background
    sf::Sprite sprite;
    sf::Texture t_blank;
    sf::Texture t_hover;
    sf::Texture t_selected;
    sf::Texture t_clicked;
};
