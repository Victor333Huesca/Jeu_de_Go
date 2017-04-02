#pragma once
#include "Choice.h"
#include "Globals.h"

class Choice_miniature : public Choice
{
public:
	Choice_miniature(sf::Vector2f pos, std::function<int(const sf::RenderTarget& window)> _Run, sf::Vector2f scale = sf::Vector2f(1, 1));
	Choice_miniature(float posX, float posY, std::function<int(const sf::RenderTarget& window)> _Run, sf::Vector2f scale = sf::Vector2f(1, 1));


	// Overide
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
	virtual void loadTextures(const sf::Texture& blank, const sf::Texture& selected);

private:
	sf::Texture t_miniature;
	sf::Texture t_selected;

	sf::Sprite s_selected;
};
