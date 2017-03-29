#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Choice: public sf::Drawable
{
public:
	Choice(const char* name, const sf::Text& text_style, sf::Vector2f pos, sf::Vector2f sc, const char*);
	Choice(const char* name, const sf::Text& text_style, float posX, float posY, sf::Vector2f sc, const char*);
    
	~Choice();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
    sf::Vector2f getSize() const;

	void move(const sf::Vector2f& offset);

	void loadTextures(const sf::Texture& blank, const sf::Texture& selected);

private:
    // Somes infos
    bool selected;

	// Item itself
	sf::Text text;
    sf::Sprite sprite;

	// Textures
	const sf::Texture* t_blank;
	const sf::Texture* t_selected;
};
