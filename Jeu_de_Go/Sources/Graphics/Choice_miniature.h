#pragma once
#include "Choice.h"
#include "Globals.h"

class Choice_miniature : public Choice
{
public:
	Choice_miniature(const char* _texture, sf::Vector2f pos, std::function<int(const sf::RenderTarget& window)> _Run, sf::Vector2f scale = sf::Vector2f(1, 1));
	Choice_miniature(const char* _texture, float posX, float posY, std::function<int(const sf::RenderTarget& window)> _Run, sf::Vector2f scale = sf::Vector2f(1, 1));

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;

private:
	sf::Texture texture;
};
