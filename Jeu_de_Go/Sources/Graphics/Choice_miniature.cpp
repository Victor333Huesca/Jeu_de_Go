#include "Choice_miniature.h"



Choice_miniature::Choice_miniature(const char* _texture, sf::Vector2f pos, std::function<int(const sf::RenderTarget&window)> _Run, sf::Vector2f scale) :
	Choice(pos, _Run)
{
	texture.loadFromFile(_texture);
	std::cout << "@Texture : " << &texture << "    -->    ";
	Choice::loadTextures(&texture, nullptr, nullptr);
}

Choice_miniature::Choice_miniature(const char* _texture, float posX, float posY, std::function<int(const sf::RenderTarget&window)> _Run, sf::Vector2f scale) :
	Choice_miniature(_texture, sf::Vector2f(posX, posY), _Run)
{
}

void Choice_miniature::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	std::cout << "Vat planter !" << std::endl;
	Choice::draw(target, states);
	std::cout << "A plante !" << std::endl;
}
