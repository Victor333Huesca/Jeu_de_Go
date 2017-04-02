#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <functional>

class Choice: public sf::Drawable
{
public:
	Choice(const char* name, const sf::Text& text_style, sf::Vector2f pos, std::function<int(const sf::RenderTarget& window)> _Run, sf::Vector2f scale = sf::Vector2f(1, 1));
	Choice(const char* name, const sf::Text& text_style, float posX, float posY, std::function<int(const sf::RenderTarget& window)> _Run, sf::Vector2f scale = sf::Vector2f(1, 1));
    
	~Choice();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
    sf::Vector2f getSize() const;

	// Pas certain de son utilit� � celle-ci, elle va surement sauter.
	void move(const sf::Vector2f& offset);

	// Charge les attributs communs pour un groupe d'item (i.e. un choix ne peut vivre sans le menu auquel il appartient).
	void loadTextures(const sf::Texture& blank, const sf::Texture& selected);
	void setFont(const sf::Font& font);

	// Permet de changer l'�tat du choix
	void setSelected(bool state = true);

	// Permet de r�cuperer sa boite englobante
	sf::FloatRect getGlobalBounds() const;

	// Applique la texture correspondant � l'�tat actuel de l'item
	void updateTexture();


	// Ceci est exp�rimental x)
	const std::function<int(const sf::RenderTarget&)> Run;

	// Principalment pour le debugage...
	std::string getName() const;
	const sf::Texture* getTextureAdress() const;

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
