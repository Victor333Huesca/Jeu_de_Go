#include "Choice.h"


Choice::Choice(sf::Vector2f pos, std::function<int(const sf::RenderTarget& window)> _Run, sf::Vector2f scale) :
	Run(_Run),
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
}

Choice::Choice(float posX, float posY, std::function<int(const sf::RenderTarget& window)> _Run, sf::Vector2f scale) :
	Choice(sf::Vector2f(posX, posY), _Run, scale)
{
}

Choice::~Choice()
{
}

void Choice::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states);
	if (selected || hover)	target.draw(effect, states);
}

sf::Vector2f Choice::getSize() const
{
    return sf::Vector2f(sprite.getTextureRect().width, sprite.getTextureRect().height);
}

void Choice::loadTextures(const sf::Texture& _texture, const sf::Texture& selected, const sf::Texture& hover)
{
	// Set texutes
	texture = &_texture;
	t_selected = &selected;
	t_hover = &hover;

	// Apply the one should be
	updateTexture();
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
