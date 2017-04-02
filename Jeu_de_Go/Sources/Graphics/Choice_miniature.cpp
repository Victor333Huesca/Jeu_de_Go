#include "Choice_miniature.h"



Choice_miniature::Choice_miniature(sf::Vector2f pos, std::function<int(const sf::RenderTarget&window)> _Run, sf::Vector2f scale) :
	Choice(pos, _Run)
{
}

Choice_miniature::Choice_miniature(float posX, float posY, std::function<int(const sf::RenderTarget&window)> _Run, sf::Vector2f scale) :
	Choice_miniature(sf::Vector2f(posX, posY), _Run)
{
}

void Choice_miniature::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite, states);
	target.draw(s_selected, states);
}

void Choice_miniature::loadTextures(const sf::Texture & blank, const sf::Texture & selected)
{
	
}
