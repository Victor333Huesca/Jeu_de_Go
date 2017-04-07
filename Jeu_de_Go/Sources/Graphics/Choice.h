#pragma once
#include "Globals.h"
#include <string>
#include <functional>
#include <iostream>
#include "Game/Game_window.h"

class Choice: public sf::Drawable
{
public:
	Choice(sf::Vector2f pos, std::function<int(const sf::RenderTarget&, Game_window&)> _Run, sf::Vector2f scale = sf::Vector2f(1, 1));
	Choice(float posX, float posY, std::function<int(const sf::RenderTarget&, Game_window&)> _Run, sf::Vector2f scale = sf::Vector2f(1, 1));
    
	virtual ~Choice();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
    sf::Vector2f getSize() const;

	// Charge les attributs communs pour un groupe d'item (i.e. un choix ne peut vivre sans le menu auquel il appartient).
	virtual void loadTextures(const sf::Texture* _texture, const sf::Texture* selected, const sf::Texture* hover);

	// Permet de changer l'état du choix
	void setSelected(bool state = true);
	void setHover(bool state = true);

	// Permet de récuperer sa boite englobante
	sf::FloatRect getGlobalBounds() const;

	// Applique la texture correspondant à l'état actuel de l'item
	void updateTexture();

	// Evenement en cas de click
	int Run(const sf::RenderTarget& window, Game_window& game);

	// Pour le debugg
	virtual void showAdressTextures() const;

private:
    // Somes infos
    bool selected;
	bool hover;

	// Textures
	const sf::Texture* texture;
	const sf::Texture* t_selected;
	const sf::Texture* t_hover;
	
	// Itself and its current effects
	sf::Sprite sprite;
	sf::Sprite effect;

	// Fonction a appeller lors du click
	const std::function<int(const sf::RenderTarget&, Game_window&)> run;
};
