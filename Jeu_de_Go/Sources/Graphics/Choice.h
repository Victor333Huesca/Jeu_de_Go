#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Choice: public sf::Drawable
{
public:
	Choice(const char* name, sf::Vector2f pos, sf::Vector2f sc,const char*,const char*);
	Choice(const char* name, float posX, float posY, sf::Vector2f sc,const char*,const char*);
    
	~Choice();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
    sf::Vector2f getSize() const;

	void move(const sf::Vector2f& offset);

	bool Click(int x, int y);

	void setSelected(bool);
	bool getSelected(); 
	void loadTextures(const sf::Texture& blank, const sf::Texture& selected);
	std::string id;
private:
    // Somes infos
    bool selected;
	
	// Item itself
	sf::Text text;
    sf::Sprite sprite;
	sf::Sprite sprite2;
	// Textures
	sf::Texture te;
	sf::Texture sf;
	sf::Font font;
	const sf::Texture* t_blank;
	const sf::Texture* t_selected;
};
