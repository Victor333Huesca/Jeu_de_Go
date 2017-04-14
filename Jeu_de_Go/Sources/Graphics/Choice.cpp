#include "Choice.h"


Choice::Choice(sf::Vector2f pos, std::function<Screens(const sf::RenderTarget&, Game_window&)> _Run, sf::Vector2f scale) :
	run(_Run),
	selected(false),
	hover(false),
	texture(nullptr),
	t_selected(nullptr),
	t_hover(nullptr)
{
    sprite.setPosition(pos);
	sprite.setScale(scale);

	effect.setPosition(pos);
	effect.setScale(scale);

#if __ERROR_LEVEL__ > 0
	log_file << "Choice::Choice(), ";
#endif // __ERROR_LEVEL__ > 0
}

Choice::Choice(float posX, float posY, std::function<Screens(const sf::RenderTarget&, Game_window&)> _Run, sf::Vector2f scale) :
	Choice(sf::Vector2f(posX, posY), _Run, scale)
{
}

Choice::~Choice()
{
#if __ERROR_LEVEL__ > 0
	log_file << "Choice::~Choice()" << std::endl;
#endif // __ERROR_LEVEL__ > 0
}

void Choice::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	assert(sprite.getTexture() != nullptr);

	target.draw(sprite, states);
	if (selected || hover)	target.draw(effect, states);
}

sf::Vector2f Choice::getSize() const
{
    return sf::Vector2f((float)sprite.getTextureRect().width, (float)sprite.getTextureRect().height);
}

void Choice::loadTextures(const sf::Texture* _texture, const sf::Texture* selected, const sf::Texture* hover)
{
	// Set textures if specified
	if (_texture != nullptr)	texture = _texture;
	if (selected != nullptr)	t_selected = selected;
	if (hover != nullptr)		t_hover = hover;

	// Apply the one should be
	updateTexture();

#if __ERROR_LEVEL__ > 0
	log_file << "Choice::loadTextures(), ";
#endif // __ERROR_LEVEL__ > 0
}

void Choice::setSelected(bool state)
{
	selected = state;
	updateTexture();
}

void Choice::setHover(bool state)
{
	hover = state;
	updateTexture();
}

sf::FloatRect Choice::getGlobalBounds() const
{
	return sprite.getGlobalBounds();
}

void Choice::updateTexture()
{
	sprite.setTexture(*texture);

	if (selected)	effect.setTexture(*t_selected);
	else if (hover)	effect.setTexture(*t_hover);
}

Screens Choice::Run(const sf::RenderTarget& window, Game_window& game)
{
	return run(window, game);
}

void Choice::showAdressTextures() const
{
	std::cout << "\n  - Choix : " <<
		"\n    - Normale : " << texture <<
		"\n    - Selected : " << t_selected <<
		"\n    - Hover : " << t_hover <<
		"\n    ---> Current : " << sprite.getTexture();
}
