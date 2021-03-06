﻿#pragma once
#include "Choice.h"

class Choice_miniature : public Choice
{
public:
	Choice_miniature(const char* _texture, sf::Vector2f pos, std::function<Screens(sf::RenderTarget&, Go_Solver&)> _Run, sf::Vector2f scale = sf::Vector2f(1, 1));
	Choice_miniature(const char* _texture, float posX, float posY, std::function<Screens(sf::RenderTarget&, Go_Solver&)> _Run, sf::Vector2f scale = sf::Vector2f(1, 1));

	virtual ~Choice_miniature();

	// Debugg
	virtual void showAdressTextures() const;

private:
	std::reference_wrapper<sf::Texture> texture;
};
