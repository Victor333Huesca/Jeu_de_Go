#include "Choice_miniature.h"



Choice_miniature::Choice_miniature(const char* _texture, sf::Vector2f pos, std::function<int(const sf::RenderTarget&window)> _Run, sf::Vector2f scale) :
	Choice(pos, _Run),
	texture(*new sf::Texture())
{
	texture.get().loadFromFile(_texture);

	Choice::loadTextures(&texture.get(), nullptr, nullptr);
}

Choice_miniature::Choice_miniature(const char* _texture, float posX, float posY, std::function<int(const sf::RenderTarget&window)> _Run, sf::Vector2f scale) :
	Choice_miniature(_texture, sf::Vector2f(posX, posY), _Run)
{
}

Choice_miniature::~Choice_miniature()
{
	log_file << "~Choice_miniature()\n";
	//delete &texture.get();
}

void Choice_miniature::showAdressTextures() const
{
	Choice::showAdressTextures();
}
