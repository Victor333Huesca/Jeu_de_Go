#include "Choice_miniature.h"



Choice_miniature::Choice_miniature(const char* _texture, sf::Vector2f pos, std::function<Screens(const sf::RenderTarget&, Game_window&)> _Run, sf::Vector2f scale) :
	Choice(pos, _Run, scale),
	texture(*new sf::Texture())
{
	texture.get().loadFromFile(_texture);

	Choice::loadTextures(&texture.get(), nullptr, nullptr);

#if __ERROR_LEVEL__ > 0
	log_file << "Choice_miniature::Choice_miniature(), ";
#endif // __ERROR_LEVEL__ > 0
}

Choice_miniature::Choice_miniature(const char* _texture, float posX, float posY, std::function<Screens(const sf::RenderTarget&, Game_window&)> _Run, sf::Vector2f scale) :
	Choice_miniature(_texture, sf::Vector2f(posX, posY), _Run, scale)
{
}

Choice_miniature::~Choice_miniature()
{
	//delete &texture.get();
#if __ERROR_LEVEL__ > 0
	log_file << "Choice_miniature::~Choice_miniature(), ";
#endif // __ERROR_LEVEL__ > 0
}

void Choice_miniature::showAdressTextures() const
{
	Choice::showAdressTextures();
}
